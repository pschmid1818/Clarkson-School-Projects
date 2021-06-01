package hw4.p1;

import java.util.concurrent.ThreadLocalRandom;

public class Client1 {
    public static void main(String[] args) {
	if (args.length != 3) {
	    System.err.println("usage: Client1 <MAX_LEFT> <MAX_RIGHT> <NUM_LISTS>");
	    System.exit(1);
	}
	
	int MAX_LEFT = 0;
	int MAX_RIGHT = 0;
	int NUM_LISTS = 0;	
	
	try {
	    MAX_LEFT = Integer.parseInt(args[0]); //left endpoint
	    MAX_RIGHT = Integer.parseInt(args[1]); //right endpoint
	    NUM_LISTS = Integer.parseInt(args[2]); //number of lists
	} catch (NumberFormatException e) {
	      System.err.println("usage: arguments must be integers.");
	      System.exit(1);
	}

	RThread[] thr = new RThread[NUM_LISTS];
	for (int i = 0; i < NUM_LISTS; i++) {
	    int left = ThreadLocalRandom.current().nextInt(0, MAX_LEFT);
	    int right = ThreadLocalRandom.current().nextInt(MAX_LEFT+1, MAX_RIGHT);
	    String label = "rt_" + i;

	    //the range is [left, right]; note that 0<left<MAX_LEFT<right<MAX_RIGHT
	    //this thread should average the numbers {sqrt(left), sqrt(left+1), ... sqrt(right)}
	    thr[i] = new RThread(label, left, right);
	    thr[i].start();
	}

	for (int i = 0; i < NUM_LISTS; i++) {
	    try {
		thr[i].join();
	    } catch (InterruptedException e) {
		e.printStackTrace();
	    }
	   
	}

    }
}
