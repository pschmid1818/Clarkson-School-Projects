import java.io.*;
import java.net.*;
import java.lang.String;



class Telephone{
    public static void main(String args[]) throws Exception
    {
	Boolean originator;
	Integer listeningPort;
	String connectToHost;
	Integer connectToPort;

	if (args.length != 4){
	    System.out.println(args.length);
	    System.out.println("usage: isOrigin(0/1) listeningPortNum connectToHost connectToPort");
	    System.exit(-1);
	}

	if (args[0].compareTo("0") ==0){
	    originator = false;
	} else {
	    originator = true;
	    System.out.println("isOriginator");
		
	}

	listeningPort = Integer.parseInt(args[1]);
	connectToHost = args[2];
	connectToPort = Integer.parseInt(args[3]);


	if (originator){
	    String origMessage;
	    String finalMessage;

	    origMessage = "This is a hardcoded message for now\n";

	    doClient(origMessage, connectToHost, connectToPort);

	    finalMessage = doServer(listeningPort);

   //	    compareMessage(origMessage, finalMessage);

	    
	    
	} else {
	    String message = doServer(listeningPort);

	    /* Client sleeps a little to let server get set up - 4 seconds 
	       May not need but why is this a good idea to be safe ?
	     */
	    
	    System.out.println("Waiting...");
	    try{
		Thread.sleep(4000);
	    } catch (InterruptedException ex){
		Thread.currentThread().interrupt();
	    }
	    
	    doClient(message, connectToHost, connectToPort);
	}
    }

    private static void doClient(String message, String connectionHost, Integer connectionPort) throws IOException
    {

	String sentence;
        String serverSentence;


        BufferedReader inFromUser=new BufferedReader(new InputStreamReader(System.in));

	System.out.println("Connecting to " + connectionHost + " port " + connectionPort + "...");


        Socket clientSocket=new Socket(connectionHost, connectionPort);
	
        DataOutputStream outToServer=new DataOutputStream(clientSocket.getOutputStream());
	
	BufferedReader inFromServer=new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

	//Client speaks first
        System.out.println("SENDING HELLO FROM CLIENT...\n");
        outToServer.writeBytes("HELLO FROM CLIENT\n");
		
	//If you want the client to write a message 
	//should also make the server read the message
	//        outToServer.writeBytes(message);

	//Client listens second	
        System.out.println("READING MESSAGE FROM SERVER...\n");
	serverSentence=inFromServer.readLine();
        System.out.println("THEY SAID: "+ serverSentence);



	inFromServer.close();
	inFromUser.close();
	clientSocket.close();
	

    }

    private static String doServer(Integer portNum) throws IOException
    {

	ServerSocket doorbellSocket = null;
	String clientLine;

        try {

	    doorbellSocket = new ServerSocket(portNum);
	} catch (IOException e) {
	    System.out.println("Could not listen on port " + portNum);
	    System.exit(-1);
	}

	System.out.println("Listening for an incoming connection on port " + portNum + "...");


	Socket connectionSocket;
	connectionSocket = doorbellSocket.accept();
	
	//Write a line that says received a connection from X

	BufferedReader inFromClient= new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
	DataOutputStream outToClient=new DataOutputStream(connectionSocket.getOutputStream());

	//Server receives a message first
        System.out.println("READING MESSAGE FROM CLIENT...\n");
	clientLine = inFromClient.readLine();

        System.out.println("THEY SAID: "+ clientLine);

	//Server sends message second
	System.out.println("Sending HELLO FROM SERVER...\n");
	outToClient.writeBytes("HELLO FROM SERVER\n");

	inFromClient.close();
	outToClient.close();
	connectionSocket.close();

	return clientLine;
    }
}
