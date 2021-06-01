import socket, threading, struct, re, time, traceback

VERSION = '1.0'

BASIC_NAME = re.compile(b'[a-zA-Z0-9.,-]+')

#defining new exceptions

class NotAUniqueName(Exception):
    pass

class ProtocolViolation(Exception):
    pass

class FrameTooLarge(ProtocolViolation):
    pass

class InvalidName(ProtocolViolation):
    pass

def int_to_u32be(i):
    return struct.pack('>L', i)

def u32be_to_int(b):
    return struct.unpack('>L', b)[0]

SIZE_OF_CHUNK_HDR = struct.calcsize('>L')  # This _should_ be 4 (bytes)

#reads all amount bytes
def read_all(sock, amt):
    buf = b''

    while len(buf) < amt:
        #TODO: receive the remaining amount of data (one line of code to be filled)
        data = sock.recv(amt-len(buf))
        if not data:
            raise EOFError("While reading from socket:", sock)
        buf += data

    return buf

#reads but does not return amt bytes
def discard_all(sock, amt, max_buffer = 65536):
    while amt > 0:
        #TODO: receive up to max_buffer or amount (which ever is less!) into data (one line of code to be filled)
        data = sock.recv(min([max_buffer, amt]))
        if not data:
            raise EOFError("While discarding from socket:", sock)
        amt -= len(data)


class Frame(object):
    def __init__(self, *chunks):
        if not all(len(chunk) > 0 for chunk in chunks):
            raise ValueError("Empty chunk in args", chunks)

        self.chunks = chunks


    #write the frame to TCP connection
    def write_to(self, sock):
        print('%r <- %r' % (sock.getsockname(), self.chunks))
        for chunk in self.chunks:
            #TODO: use sock.sendall() to send this non empty chunk according to the protocol (2 lines of code to be filled) 
            sock.sendall(int_to_u32be(len(chunk)))
            sock.sendall(chunk)
        sock.sendall(int_to_u32be(0))  # Write the sentinel chunk (1.0, 4)

    @classmethod
    #read a frame from the TCP connection returning a new object
    def read_from(cls, sock, max_size = None):
        chunks = []
        cur_size = 0

        while True:
            chunk_len = u32be_to_int(read_all(sock, SIZE_OF_CHUNK_HDR))
            if chunk_len == 0:  # Read a sentinel chunk (1.0, 4)
                break

            cur_size += chunk_len
            if max_size is not None and cur_size > max_size:
                # It is crucial to synchronize the protocol, at least, by discarding the necessary data
                discard_all(sock, chunk_len)
            else:
                chunks.append(read_all(sock, chunk_len))

        print('%r -> %r' % (sock.getsockname(), chunks))

        if not chunks:
            raise ValueError("Read an empty frame")

        if max_size is not None and cur_size > max_size:
            raise FrameTooLarge(cur_size)

        return cls(*chunks)

#client object: the servers view of a client
class Client(object):
    def __init__(self, sock, name, server):
        self.socket = sock
        self.name = name
        self.server = server

        self.alive = True

        self.write_queue = []
        self.write_condition = threading.Condition()  # Notified when a Frame is ready to send
        self.write_event = threading.Event()  # Set when the writer thread is listening
        self.write_thread = threading.Thread(
                name = 'Client-' + name.decode() + '-write',
                target = self.thread_write_run,
        )

        self.read_thread = threading.Thread(
                name = 'Client-' + name.decode() + '-read',
                target = self.thread_read_run,
        )

        with server.lock:
            if name in server.clients:
                raise NotAUniqueName(name)

            server.clients[name] = self

        self.write_thread.start()
        self.read_thread.start()

    @classmethod
    def is_valid_name(cls, name):
        return bool(BASIC_NAME.match(name))

    def thread_write_run(self):
        with self.write_condition:
            self.write_event.set()

            while True:
                self.write_condition.wait()  # Releases the lock

                if not self.alive:
                    return

                if not self.write_queue:
                    continue

                frame = self.write_queue.pop(0)
                frame.write_to(self.socket)

    def enqueue(self, frame):
        self.write_event.wait()
        with self.write_condition:
            self.write_queue.append(frame)
            self.write_condition.notify()

    def thread_read_run(self):
        while self.alive:
            try:
                frame = Frame.read_from(self.socket, self.server.max_size)
                self.handle(frame)
            except EOFError:
                self.close(b'End of stream')
            except Exception as e:
                traceback.print_exc()
                self.enqueue(Frame(b'ERR', b'Exception: ' + repr(e).encode()))

    def close(self, reason = b'Unknown close reason'):
        # This may discard unsent messages; it doesn't really matter, though.
        try:
            Frame(b'CLOSE', reason).write_to(self.socket)
        except Exception as e:
            traceback.print_exc()
            print('Failed to write CLOSE to %r: %r' % (self, e))

        # Inform other clients that this connection is closing
        observers = set()  # of Client

        with self.server.lock:
            for channel in self.member_channels():
                observers.update(channel.clients.difference(set([self])))
                channel.remove(self)

        for client in observers:
            client.enqueue(Frame(b'QUIT', self.name, reason))

        self.alive = False
        # Also tell the writer that it is time to die
        with self.write_condition:
            self.write_condition.notify()

        # Remove this client from ONLINE
        with self.server.lock:
            try:
                del self.server.clients[self.name]
            except KeyError:
                print('WARN: failed to remove non-existent %r' % (self,))

        # End the connection
        self.socket.shutdown(socket.SHUT_RDWR)
        self.socket.close()
        self.socket = None

    def member_channels(self):
        channels = set()

        with self.server.lock:
            for chan in self.server.channels.values():
                if self in chan:
                    channels.add(chan)

        return channels

    def handle(self, frame):
        try:
            self.HANDLERS.get(frame.chunks[0], self.handle_unknown)(self, frame)
        except Exception as e:
            traceback.print_exc()
            self.enqueue(Frame(b'ERR', b'Exception during command handling: ' + repr(e).encode()))

    def handle_unknown(self, frame):
        self.enqueue(Frame(b'ERR', b'Unknown message kind: ' + frame.chunks[0]))

    def handle_msg(self, frame):
        if len(frame.chunks) < 3:
            self.enqueue(Frame(b'ERR', b'Not enough arguments to MSG'))
            return

        with self.server.lock:
            try:
                target = self.server.get_destination(frame.chunks[1])
            except KeyError:
                self.enqueue(Frame(b'ERR', b'No target by that name'))
            else:
                target.enqueue(Frame(b'MSG', self.name, frame.chunks[1], frame.chunks[2]))

    def handle_join(self, frame):
        if len(frame.chunks) < 2:
            self.enqueue(Frame(b'ERR', b'Not enough arguments to JOIN'))
            return

        if not Channel.is_valid_name(frame.chunks[1]):
            self.enqueue(Frame(b'ERR', b'Invalid name: ' + frame.chunks[1]))
            return

        with self.server.lock:
            self.server.get_or_create_channel(frame.chunks[1]).join(self)

    def handle_leave(self, frame):
        if len(frame.chunks) < 2:
            self.enqueue(Frame(b'ERR', b'Not enough arguments to LEAVE'))
            return

        with self.server.lock:
            try:
                channel = self.server.channels[frame.chunks[1]]
            except KeyError:
                self.enqueue(Frame(b'ERR', b'No such channel'))
                return

        channel.leave(self)

    def handle_quit(self, frame):
        reason = b'No reason given'

        if len(frame.chunks) > 1:
            reason = frame.chunks[1]

        self.close(reason)

    def handle_online(self, frame):
        with self.server.lock:
            self.enqueue(
                    Frame(b'ONLINE', *(cli.name for cli in self.server.clients.values()))
            )

    def handle_list(self, frame):
        with self.server.lock:
            self.enqueue(
                    Frame(b'LIST', *(channel.name for channel in self.server.channels.values()))
            )

    def handle_members(self, frame):
        if len(frame.chunks) < 2:
            self.enqueue(Frame(b'ERR', b'Not enough arguments to MEMBERS'))
            return

        with self.server.lock:
            try:
                channel = self.server.channels[frame.chunks[1]]
            except KeyError:
                self.enqueue(Frame(b'ERR', b'No such channel'))
                return

            self.enqueue(
                    Frame(b'MEMBERS', channel.name, *(cli.name for cli in channel.clients))
            )

    HANDLERS = {
            b'MSG': handle_msg,
            b'JOIN': handle_join,
            b'LEAVE': handle_leave,
            b'QUIT': handle_quit,
            b'ONLINE': handle_online,
            b'LIST': handle_list,
            b'MEMBERS': handle_members,
    }

class Channel(object):
    def __init__(self, name, server):
        self.name = name
        self.server = server
        self.clients = set()

        with server.lock:
            if name in server.channels:
                raise NotAUniqueName(name)
            server.channels[name] = self

    @classmethod
    def is_valid_name(cls, name):
        return name.startswith(b'#') and bool(BASIC_NAME.match(name[1:]))

    def add(self, client):
        self.clients.add(client)

    def remove(self, client):
        self.clients.discard(client)

        # If no more clients exist in this channel (after removal), delete this channel
        if not self.clients:
            with self.server.lock:
                try:
                    del self.server.channels[self.name]
                except KeyError:
                    print('WARN: failed to remove non-existent %r' % (self,))

    def __contains__(self, client):
        return client in self.clients

    def enqueue(self, frame):
        for cli in self.clients:
            cli.enqueue(frame)

    def join(self, client):
        if client not in self:
            self.add(client)
            self.enqueue(Frame(b'JOIN', self.name, client.name))

    def leave(self, client):
        if client in self:
            self.enqueue(Frame(b'LEAVE', self.name, client.name))
            self.remove(client)

class Server(object):
    def __init__(self, name, version = None, max_size = 2048, backlog = 8):
        self.name = name
        if not isinstance(self.name, bytes):
            self.name = self.name.encode()

        self.version = version if version is not None else VERSION.encode()
        self.max_size = max_size
        self.backlog = backlog

        self.lock = threading.RLock()
        self.clients = {}  # name -> Client
        self.channels = {}  # name -> Channel

        self.listening_threads = set()
        self.listening_sockets = set()

    def get_destination(self, name):
        if name in self.clients:
            return self.clients[name]

        if name in self.channels:
            return self.channels[name]

        raise KeyError(name)

    def get_or_create_channel(self, name):
        if name in self.channels:
            return self.channels[name]

        if not Channel.is_valid_name(name):
            raise InvalidName(name)

        return Channel(name, self)  # Constructor registers this object to self

    #add the listening socket to the server
    def add_listener(self, sock):
        self.listening_threads.add(threading.Thread(
                name = 'Server-listener-' + repr(sock.getsockname()),
                #thread_listen_run is going to be called in a new thread with one argument (socket)
                target = self.thread_listen_run,
                args = (sock,)
        ))
        self.listening_sockets.add(sock)

    #starts the listening threads and waits to be intterupted to be shutting down
    def serve(self):
        #you can't run a server that does not listen 
        if not self.listening_sockets:
            raise RuntimeError("Server told to serve on no sockets:", self)

        #kickoff the thread
        with self.lock:
            for thread in self.listening_threads:
                thread.start()

        #catches exceptions (sleep for ever) waiting to be interrupted 
        try:
            while True:
                time.sleep(3600)
        #if interrupted shuts down
        except KeyboardInterrupt:
            print('Server shutting down...')
            for client in self.clients.values():
                client.close(b'Server shutting down')

        #terminate the threads        
        with self.lock:
            for sock in self.listening_sockets:
                # Crash the listening thread
                sock.close()  

        #allows one thread to wait until another thread completes its execution.
        for thread in self.listening_threads:
            thread.join()

    #the thread that is actually responsible for listening on the given socket
    def thread_listen_run(self, sock):
        #TODO: set socket to listen with backlog of self.backlog (one line to be filled)
        sock.listen(self.backlog);
        # Allow accept() to return occasionally to catch a closed socket
        sock.settimeout(1)  

        while True:
            try:
                connection, address = sock.accept()
            except socket.timeout:
                continue
            except socket.error:
                print('%s: socket closed, stopping' % (threading.current_thread().name,))
                return

            #a new thread for handling the connection
            threading.Thread(
                    name = 'Connection-from-' + repr(address),
                    #call the function thread_initial_connection_run 
                    target = self.thread_initial_connection_run,
                    args = (connection,)
            ).start()


    #the new connection is handled by the thread above
    def thread_initial_connection_run(self, connection):
        # Generally, propagate exceptions; it's okay if this thread crashes, it will not affect the listener.
        Frame(b'HELLO', self.name, self.version).write_to(connection)

        def send_close(reason):
            try:
                Frame(b'CLOSE', reason).write_to(connection)
            except Exception as e:
                traceback.print_exc()
                print('Failed to write CLOSE to starting connection: %r' % (e,))

        try:
            initial = Frame.read_from(connection)
            
            if initial.chunks[0] != b'USER':
                raise ProtocolViolation("Expected USER Frame")

            if len(initial.chunks) < 2:
                raise ProtocolViolation("Expected name in USER Frame")

            if not Client.is_valid_name(initial.chunks[1]):
                raise InvalidName(initial.chunks[1])

            cli = Client(connection, initial.chunks[1], self)  # Constructor initializes all threads and registers to self
            cli.enqueue(initial)
        except Exception as e:
            traceback.print_exc()
            send_close(b'Exception during connection: ' + repr(e).encode())

def main():
    import argparse

    #parse the command line arguments
    parser = argparse.ArgumentParser(description = 'Run the chatd server')
    parser.add_argument('-H', '--host', action = 'append', help = 'Host (address) to bind to (default all interfaces/all network protocols)')
    parser.add_argument('-P', '--port', type = int, help = 'Port to bind to (default 12074)', default = 12074)
    parser.add_argument('--max-size', type = int, help = 'Maximum number of bytes per frame (total in all chunks; default 2048)', default = 2048)
    parser.add_argument('-n', '--name', help='Name of this server (as reported in HELLO; default "chatd")', default = 'chatd')
    parser.add_argument('--backlog', type = int, help = 'Number of backlogged connectors (passed to listen; default 8)', default = 8)

    args = parser.parse_args()

    server = Server(args.name.encode(), None, args.max_size, args.backlog)

    #if no bind addresses were given, just use the default (IPV4)
    if not args.host:
        #TODO: construct the socket which is called ipv4_sock (one line of code to be filled)
        ipv4_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        #allow the listening socket to be resused and dont wait for old closing connections
        ipv4_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        #TODO: bind to '' (empty string means all interfaces) on port args.port (one line of code to be filled)
        ipv4_sock.bind(('', 2014))
        #takes a listening socket and just listens (function call)
        server.add_listener(ipv4_sock)
        #server.add_listener(ipv6_sock)
    else:
        #if it looks like an ipv6 (has a :) then use IPV6 as an address family
        for host in args.host:
            sock = socket.socket(socket.AF_INET6 if ':' in host else socket.AF_INET)
            #bind the explicitly given address 
            sock.bind((host, args.port))
            #add the listening socket to the server
            server.add_listener(sock)
    #serve until the server is told to shutdown (function call)
    server.serve()

#the program starts here
if __name__ == '__main__':
    main()
