In this code Dominic Romano and I worked together as we emailed you. We both made it on Dom's computer as we are roommates and then sent the "python" directory to me.
Dom has experience socket coding so he showed me how what functions we neede and how to implement them.
As a software engineer, I know python fairly well so I helped dom with the syntax in python and how to implement the printing in MyPrint.

After getting a code that worked with echobot we sent the code over to my computer to test it with one another. We then encountered our first major issue, we wern't receiving each others messages.
We then asked a friend, Ted Kane to help us and send us a message which we never got. He did get our messages though.
We fixed this by waiting for a responce with if(inData != ''). This waited for an incomming message.
This led to a new issue that we weren't able to fix though. We need a response in order to continue or else we are stick in the loop. 
It also broke the else in MyPrint that handled invalid commands also getting caught in the loop. 
The only way to get out of the loop is ctrl^c to break out of the code, this logs you out of the server as well.

A final minor error we encountered was due to the order that our code executes and takes in responses, we receive a response one out of order. 
This isn't code breaking and when using a command ,like JOIN, LEAVE, or ONLINE, because we get a response we can hit enter with a blank line and won't get caught in the loop.

Finally, we decided on hard coding connection as typing a command line argument every time for testing was annoying.

Client Transcripts:

[schmidp@opsys:~/cs455/python]$ python3 SocketClient.py
Enter Prefered Username: schmidp


HELLO
Server: chatd@comm
Version1.0


schmidp >> ONLINE


User Accepted: schmidp


schmidp >> MSG echobot "hi"


Online:
grissess
echobot
lynden
schmidp


schmidp >> LIST


From: echobot/To: schmidp
Message: "hi"


schmidp >>


Channels:
#echo
#chat


schmidp >> JOIN #echo


schmidp has joined #echo


schmidp >> MEMBERS #echo
schmidp >>


Channel:#echo
Members of Channel:
echobot
schmidp
grissess


schmidp >> LEAVE #echo


schmidp has left #echo


schmidp >> QUIT


GOODBYE: No reason given




For the server all I did was go through the TODOs and do what it said.

Server Transcripts: (Copied by hand from lab video - forgot to copy and paste somewhere in lab)

[schmidp@opsys:~/cs455/python]$ python3 server_skeleton.py
('128.153.5.164', 2014) <- (b'HELLO', b'chatd', b'1.0')
('128.153.5.164', 2014) -> [b'USER', b'morgan']
('128.153.5.164', 2014) <- (b'USER', b'morgan')
('128.153.5.164', 2014) -> [b'ONLINE']
('128.153.5.164', 2014) <- (b'ONLINE', b'morgan')
('127.0.0.1', 2014) <- (b'HELLO', b'chatd', b'1.0')
('127.0.0.1', 2014) -> [b'USER', b'simononma']
('127.0.0.1', 2014) <- (b'USER', b'simononma')
('127.0.0.1', 2014) -> [b'MSG, b'morgan', b'Hello']
('128.153.5.164', 2014) <- (b'MSG, b'simononma', b'morgan', b'Hello')
('128.153.5.164', 2014) -> [b'MSG, b'simononma', b'hi']
('127.0.0.1', 2014) <- (b'MSG, b'morgan', b'simeonma', b'Hello')
('127.0.0.1', 2014) -> [b'MSG, b'morgan', b'I received this']
('128.153.5.164', 2014) <- (b'MSG, b'simononma', b'morgan', b'I received this')
('127.0.0.1', 2014) -> [b'LIST']
('127.0.0.1', 2014) <- (b'LIST',)
('127.0.0.1', 2014) -> [b'ONLINE']
('127.0.0.1', 2014) <- (b'ONLINE, b'morgan', b'simeonma')
('127.0.0.1', 2014) -> [b'JOIN', b'#test']
('127.0.0.1', 2014) <- (b'JOIN', b'#test', b'simeonma')
('127.0.0.1', 2014) -> [b'LEAVE", b'#test']
('127.0.0.1', 2014) <- (b'LEAVE", b'#test' , b'simeonma')
('127.0.0.1', 2014) -> [b'LIST']
('127.0.0.1', 2014) <- (b'LIST',)
('127.0.0.1', 2014) -> [b'JOIN', b'#test']
('127.0.0.1', 2014) <- (b'JOIN', b'#test', b'simeonma')
('128.153.5.164', 2014) <- [b'QUIT']
('128.153.5.164', 2014) -> (b'CLOSE', b'No reason given')
 ('127.0.0.1', 2014) -> [b'LIST']
('127.0.0.1', 2014) <- (b'LIST', b'#test)
