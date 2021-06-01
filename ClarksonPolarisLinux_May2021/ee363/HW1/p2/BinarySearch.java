import java.util.Arrays;

public class BinarySearch 
{
	public static int indexOf(int[] a,int key)
	{

		int lo=0;
		int hi=a.length-1;
		int count=0;

		while(lo<=hi)
		{
			int mid=lo + (hi-lo) /2;
			
			for(int c=0; c<=count; c++)
			{
				StdOut.print("  ");
			}	
			StdOut.println("[" + lo + "," + hi + "]");
			count++;
	
			if (key<a[mid])
			{ 
				hi=mid-1;
			}
			else if (key>a[mid]) 
			{
				lo=mid+1;
			}
			
			else 
			{
				return mid;
			}
		}
		return -1;
	}
	public static void main(String[] args)
	{
		In in = new In(args[0]);
		int[] whitelist = in.readAllInts();
		Arrays.sort(whitelist);
			
		while (!StdIn.isEmpty())
		{   //read key, print if not in whitelist
			int key=StdIn.readInt();
			if (indexOf(whitelist,key)==-1)
				StdOut.println(key);
			
		}	
	}
}
