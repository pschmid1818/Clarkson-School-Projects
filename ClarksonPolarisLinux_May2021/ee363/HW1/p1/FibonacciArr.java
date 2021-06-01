
public class FibonacciArr 
{
	public static long F(int N)
	{
		if (N==0) return 0;
		if (N==1) return 1;
		return F(N-1) + F(N-2);
	}

	public static void main(String[] args)
	{
		long full[] = new long[11]; //Creates an array to store full fibonacci sequence
		
		for(int N=0; N<=10; N++) //Shortened to 10 to make full tests a reasonable time
		{
			long temp= F(N); //Creates a temp variable to show current value
			full[N]=temp; //Stores current value in array
		}
		for (int c=0; c<=10; c++)
		{
			StdOut.println(c + " " + full[c]); //Outputs the array
		}
	}
}
