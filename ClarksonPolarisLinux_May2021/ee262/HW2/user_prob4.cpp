#include<iostream>
using namespace std;

double max(double x, double y, double z);
double max(double x, double y);

int main()
{
	double num1=10;
	double num2=63;
	double num3=37;
	double ans;

	if (num2==0)
	{
		cout <<num1 <<endl;
	}
	else if (num3==0)
	{
		ans=max(num1,num2);
	}
	else
	{
		ans=max(num1,num2,num3);
	}	
	cout <<ans <<endl;
	
	return 0;
}

double max(double x, double y, double z)
{
	double ans;

	if(x>y && x>z)
	{
		ans=x;
	}
	else if(y>x && y>z)
	{
		ans=y;
	}
	else if(z>x && z>y)
	{
		ans=z;
	}
	
	return ans;
}

double max(double x, double y)
{
	double ans;
	
	if(x>y)
	{
		ans=x;
	}
	else if(y>x)
	{
		ans=y;
	}
	
	return ans;
}
