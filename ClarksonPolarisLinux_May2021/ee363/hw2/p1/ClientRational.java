package hw2.p1;

import edu.princeton.cs.algs4.StdOut;

public class ClientRational {

public static void main(String[] args) {
		Rational r1 = new Rational(5, 6);
		Rational r2 = new Rational(3, 4);
		StdOut.println("r1: " + r1);
		StdOut.println("r2: " + r2);
		

		Rational rsum = r1.plus(r2);
		StdOut.println("r1 + r2: " + rsum.numerator() + "/" + rsum.denominator());

		Rational rdiff = r1.minus(r2);
		StdOut.println("r1 - r2: " + rdiff.numerator() + "/" + rdiff.denominator());

		Rational rprod = r1.times(r2);
		StdOut.println("r1 * r2: " + rprod.numerator() + "/" + rprod.denominator());

		Rational rquot = r1.dividedBy(r2);
		StdOut.println("r1 / r2: " + rquot.numerator() + "/" + rquot.denominator());

		System.out.println();
		StdOut.println("[Rational cr1 = r1;]");
		StdOut.println("[Rational ccr1 = new Rational(r1.numerator(), r1.denominator());]");
		Rational cr1 = r1;
		Rational ccr1 = new Rational(r1.numerator(), r1.denominator());
		Rational n5 = new Rational(7, 8);
		StdOut.println("cr1: " + cr1);
		StdOut.println("ccr1: " + ccr1);
		StdOut.println("n5: " + n5);
		StdOut.println("r1 equals cr1: " + r1.equals(cr1));
		StdOut.println("r1 equals ccr1: " + r1.equals(ccr1));
		StdOut.println("r1 equals equals n5: " + r1.equals(n5));
		
		
		//use VM flag '-ea' to cause overflow exception
		StdOut.println("\nOverflow test:");
		StdOut.println("Integer.MAX_VALUE: " + Integer.MAX_VALUE);
		Rational r3 = new Rational(Integer.MAX_VALUE, 3);
		Rational r4 = new Rational(10,1);
		StdOut.println("r3: " + r3);
		StdOut.println("r4: " + r4);
		StdOut.println("Will attempt r3*r4 ...");
		Rational ofl = r3.times(r4);
		StdOut.println("r3*r4 = " + ofl);
	}

}
