import socket
import sys

Location = "comm.cslabs.clarkson.edu"
Port = 12074
Vers = "1.0"
buf = 1024

#for other peoples servers in lab
#Location = "comm.cslabs.clarkson.edu"
#Port =

def myPrint(socket, data, name = None):
    arr =[]
    pos = 0
    len = 1
    if b"\x00\x00\x00\x00" in data:        
        while len > 0:
            len = int.from_bytes(data[pos:pos + 4], "big")
            if len == 0:
                break
            pos += 4
            arr.append(data[pos:pos + len].decode())
            pos += len
        print("\n")
        if(arr[0] == "MSG"):
            print("From: " + arr[1] + "/To: " + arr[2] + "\nMessage: " + arr[3])
        elif(arr[0] == "JOIN"):
            print(arr[2] + " has joined " + arr[1]) 
        elif(arr[0] == "LEAVE"):
            print(arr[2] + " has left " + arr[1])
        elif(arr[0] == "QUIT"):
            print(arr[1] + " has been kicked for " + arr[2])
        elif(arr[0] == "ONLINE"):
            print("Online:\n" + "\n".join(arr[1:]))
        elif(arr[0] == "LIST"):
            print("Channels:\n" + "\n".join(arr[1:]))
        elif(arr[0] == "MEMBERS"):
            print("Channel:" + arr[1] + "\nMembers of Channel:\n" + "\n".join(arr[2:]))
        elif(arr[0] == "USER"):
            print("User Accepted: " + arr[1])
        elif(arr[0] == "ERR"):
            print("ERROR: " + arr[1])
        elif(arr[0] == "CLOSE"):
            print("GOODBYE: " + arr[1])
            sys.exit()
        elif(arr[0] == "HELLO"):
            if(arr[2] == Vers):
               print("HELLO\n" + "Server: " + arr[1] + "\nVersion" + arr[2])
               User(socket, name)
        else:
            print("INVALID COMMAND")
        print("\n")

def mySend(socket, arr):
    for i in arr:
        socket.sendall(len(i).to_bytes(4, "big"))
        socket.sendall(i.encode())
    socket.sendall(int.to_bytes(0, 4, "big"))

def User(socket, name):
    comm = "USER"
    array = [comm, name]
    mySend(socket, array)
    
if __name__ == "__main__":
    Username = input("Enter Prefered Username: ") 
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        sock.connect((Location, Port))
    except Exception as e: 
        print("Something is wrong with %s:%d. Exception: %s\n" % (Location, Port, e))
    finally:
        data = b''
        inData = ''
        while(True):
            data += sock.recv(buf)
            if b"\x00\x00\x00\x00" in data:
                myPrint(sock, data, Username)
                data = b''
            inData = input(f"{Username} >> ")
            byte = inData.split(" ")
            if(byte[0] == "MSG"):
                byte[2] = " ".join(byte[2:])
            if(inData != ''):
                mySend(sock, byte)
                inData = ''
        sock.close() 

