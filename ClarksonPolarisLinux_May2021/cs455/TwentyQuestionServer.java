import java.io.*;
import java.net.*;
import java.lang.String;

class TwentyQuestionsServer {
    public static void main(String arg[]) throws Exception
    {
	int MAX_QUESTIONS = 20;
	int MAX_INVALID_QUESTIONS = 3;
	String clientSentence;
	int portNum;
	BufferedReader consoleUser;
	boolean acceptAnotherClient = true;
	boolean validResponse;
	String tempString;
	int minNumberOfQuestions = MAX_QUESTIONS + 1;
	String thingToGuess;
	ServerSocket doorbellSocket = null;
	boolean seenWin = false;

	consoleUser =
	    new BufferedReader(new InputStreamReader(System.in));

	System.out.print("Enter the port number to bind the server to: ");
	tempString = consoleUser.readLine();
	
	portNum = Integer.parseInt(tempString);

        try {

	    doorbellSocket = new ServerSocket(portNum);
	} catch (IOException e) {
	    System.out.println("Could not listen on port " + portNum);
	    System.exit(-1);
	}

	System.out.println("Listening for an incoming connection on port " + portNum + "...");

	while (acceptAnotherClient) {
	    int numQuestions = 1;
	    int numIncorrectQuestions = 0;
	    String clientQuestion;
	    String userAnswer;
	    boolean clientGuessedCorrectly = false;
	    boolean legitimateQuestion;
	    boolean answerYes;
	    String clientName;

	    Socket connectionSocket;
	    connectionSocket = doorbellSocket.accept();


	    BufferedReader inFromClient = 
		new BufferedReader(
		     new InputStreamReader(connectionSocket.getInputStream() )
				   );

	    DataOutputStream outToClient = 
		new DataOutputStream(connectionSocket.getOutputStream());

	    outToClient.writeBytes("Welcome! Let's play " + MAX_QUESTIONS + "  questions!\n");
	    outToClient.writeBytes("You have connected from " + 
				   connectionSocket.getInetAddress().getHostAddress() +
				   " port " + 
				   connectionSocket.getPort() + ".\n");

	    outToClient.writeBytes("What is your name?\n");
	    clientName = inFromClient.readLine();
	    outToClient.writeBytes("Hi " + clientName+ ". Waiting for server to think of something...\n");

	    System.out.println(clientName+ " has connected to play " + MAX_QUESTIONS + " questions from "
			       + connectionSocket.getInetAddress().getHostAddress() 
			       + " port " + 
			       connectionSocket.getPort() + ".\n");

	    System.out.println("Enter something for " + clientName + " to guess. \n");
	    thingToGuess = consoleUser.readLine();
	    System.out.println("Ok. Lets see how long it takes them to guess " + thingToGuess + ".\n");

	    outToClient.writeBytes("Ok ready!\n");
	    
	    while (( numQuestions <= MAX_QUESTIONS) && 
		   !clientGuessedCorrectly &&
		   (numIncorrectQuestions < MAX_INVALID_QUESTIONS)
		   ){
		
		outToClient.writeBytes("Ask question #" + numQuestions + ":\n");
		System.out.print("Waiting for a question... \n");				   
		clientQuestion = inFromClient.readLine();
		
		System.out.print("Question " + numQuestions +": " + clientQuestion + "\n");
	    
		System.out.print("Did they guess " + thingToGuess + " correctly? Y/N:");
		clientGuessedCorrectly = GetYesOrNo(consoleUser);
		
		if (clientGuessedCorrectly){
		    System.out.print("So they won, right? Are you sure?\n");
		    clientGuessedCorrectly = GetYesOrNo(consoleUser);
		    if (clientGuessedCorrectly){

			outToClient.writeBytes("Congratulations! You win!\n");
			outToClient.writeBytes("You guessed "+ thingToGuess + " in " + numQuestions +" questions.\n");


			if (numQuestions < minNumberOfQuestions){
			    
			    
			    outToClient.writeBytes("That is a new record!\n");
			    System.out.print("That is a new record!\n");
			}
			
			if (seenWin){
			    outToClient.writeBytes("Old record is " +
						   minNumberOfQuestions + 
						   " questions.\n");
			    System.out.print("Old record is " +
						   minNumberOfQuestions + 
						   " questions.\n");
			    
			}
			minNumberOfQuestions = numQuestions;
			seenWin = true;
		    }
		} 
		if (!clientGuessedCorrectly) {
		    System.out.print("Did they send a legitimate yes or no question? Y/N:");
		    legitimateQuestion = GetYesOrNo(consoleUser);
		    
		    if (legitimateQuestion){
			
			//they are allowed several incorrect questions for each correct one
			numIncorrectQuestions=0;

			//they didn't win yet
			System.out.print("Ok then please answer their question with Y/N: "+ clientQuestion + " " );
			answerYes = GetYesOrNo(consoleUser);
			System.out.print("\n");

			if (answerYes){
			    outToClient.writeBytes("Answer #" + numQuestions + ": Yes\n");
			} else {
			    outToClient.writeBytes("Answer #" + numQuestions + ": No\n");
			}
			numQuestions++;
		    } else {
			outToClient.writeBytes("That is not a legitimate yes or no question!\n");

			numIncorrectQuestions++;
			if ( numIncorrectQuestions ==3){
			    System.out.print("That was their last chance! Closing connection...\n" );
			    outToClient.writeBytes("Three strikes you're out!\n");
			} else {
			    System.out.print("Retrying....\n" );
			}


		    }
		} //not guessed correctly

		
	    }	//while interacting with this client							 
	    
	    if ((numQuestions >= MAX_QUESTIONS) && !clientGuessedCorrectly){
		outToClient.writeBytes("Sorry, you are out of questions.\n");
		outToClient.writeBytes("It was "+ thingToGuess + "\n");
		System.out.print("They did not guess " + thingToGuess + "!\n");
	    }
	    System.out.print("Game over!\n");
	    outToClient.writeBytes("GOODBYE\n");
	    connectionSocket.close();
	    System.out.print("Would you like to accept another connection? Y/N: ");

	    acceptAnotherClient = GetYesOrNo(consoleUser);

	}
    }

    private static boolean GetYesOrNo(BufferedReader userInput) throws Exception
    {
	
	String tempString;

	while(true){
	    tempString = userInput.readLine();
	    if ((tempString.compareTo("Y")== 0) || 
		(tempString.compareTo("y")==0) ||
		(tempString.compareTo("yes")==0) ||
		(tempString.compareTo("YES")==0) )
		
	    {
		return true;
	    } else  if ((tempString.compareTo("N")== 0) || 
		(tempString.compareTo("n")==0) ||
		(tempString.compareTo("no")==0) ||
		(tempString.compareTo("NO")==0) )
		{
		return false;
	    } else {
		System.out.print("Invalid response! Enter Y or N.\n ");

	    }
	} 

    }
}
