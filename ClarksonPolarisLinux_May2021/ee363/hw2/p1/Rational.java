//Paul Schmid SE
//Evan Nguyen CE
//HW2
//Rational.java

package hw2.p1;
 
public final class Rational 
{
	final int numerator;
	final int denominator;
	
	public Rational(int numerator, int denominator)
	{
		this.numerator=numerator;
		this.denominator=denominator;
	}
	public int numerator()
	{
		return this.numerator;
	}
	public int denominator()
	{
		return this.denominator;
	}
	public Rational plus(Rational that)
	{
		int den=this.denominator*that.denominator;
			overflow(denominator,that.denominator,'*');
		int num1=this.numerator*that.denominator;
			overflow(this.numerator,that.denominator,'*');
		int num2=that.numerator*this.denominator;
			overflow(that.numerator,this.denominator,'*');
		int num=num1+num2;
			overflow(num1,num2,'+');
		
		Rational sum=simplify(num,den);
		
		return sum;
	}
	public Rational minus(Rational that)
	{
		int den=this.denominator*that.denominator;
			overflow(denominator,that.denominator,'*');
		int num1=this.numerator*that.denominator;
			overflow(this.numerator,that.denominator,'*');
		int num2=that.numerator*this.denominator;
			overflow(that.numerator,this.denominator,'*');
		int num=num1-num2;
			overflow(num1,num2,'-');
		
		Rational difference=simplify(num,den);
		
		return difference;
	}
	public Rational times(Rational that)
	{
		int den=this.denominator*that.denominator;
			overflow(this.denominator,that.denominator,'*');
		int num=this.numerator*that.numerator;
			overflow(this.numerator,that.numerator,'*');
		
		Rational product=simplify(num,den);
		
		return product;
	}
	public Rational dividedBy(Rational that)
	{
		int den=this.denominator*that.numerator;
			overflow(this.denominator,that.numerator,'*');
		int num=this.numerator*that.denominator;
			overflow(this.numerator,that.denominator,'*');
			
		Rational quotient=simplify(num,den);
		
		return quotient;
	}
	
	public Rational simplify(int num, int den)
	{
		int gcf=gcf(num,den);
		
		int numtrue=num/gcf;
		int dentrue=den/gcf;
		
		Rational simp=new Rational(numtrue,dentrue);
		
		return simp;

	}
	public int gcf(int num,int den)
	{
		if (den==0) 
		{
			return num;
		}
		else
		{
			return gcf(den,num%den);
		}

	}
	public boolean equals(Rational that)
	{
		boolean equal=false;
		if(this.numerator==that.numerator && this.denominator==that.denominator)
		{
			equal=true;
		}
		return equal;
	}
	public void overflow(int a, int b, char opp)
	{
		long a2=a;
		long b2=b;
		
		if(opp=='+')
		{
			assert a2+b2 < Integer.MAX_VALUE : "Overflow in addition";
		}
		if(opp=='-')
		{
			assert a2-b2 > Integer.MIN_VALUE : "Overflow in subtraction";
		}
		if(opp=='*')
		{
			assert a2*b2 < Integer.MAX_VALUE : "Overflow in multiplication";
		}
		return;
	}
	public String toString()
	{
		String nums=Integer.toString(this.numerator);
		String dens=Integer.toString(this.denominator);
		String rat=nums+"/"+dens;
		return rat;
	}
}
