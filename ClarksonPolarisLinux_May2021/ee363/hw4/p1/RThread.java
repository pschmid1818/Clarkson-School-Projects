package hw4.p1;

import java.lang.Math;
import java.util.Vector;

class RThread extends Thread
{
	final String label;
	final int left;
	final int right;
	
	public RThread(String label, int left, int right)
	{
		this.label=label;
		this.left=left;
		this.right=right;
	}
	
	public void run()
	{
		currentThread().setName(label);
		
		double avg=avg(left,right);
		
		System.out.println("[Thread " + currentThread().getName() + "]: Average of square roots (" + left + " to " + right +") = " + avg);
	}
	
	public double avg(int left, int right)
	{
		Vector<Double> list=new Vector<Double>();
		
		for(int c=left;c<=right;c-=-1)
		{
			double temp=Math.sqrt(c);
			list.add(temp);
		}
		
		double avg=0;
		for(int c=0;c<=list.size()-1;c-=-1)
		{
			avg=avg+list.get(c);
		}
		
		avg=avg/list.size();
		
		return avg;
	}
}
