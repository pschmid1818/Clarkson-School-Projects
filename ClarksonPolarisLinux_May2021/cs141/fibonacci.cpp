#include<iostream>
using namespace std;

int main()
{
	int var;
	int fib=1;
	int num=0;

	cout<<"Enter a positive integer: ";
	cin>>var;

	if (var>0)
	{
	cout<<"The first " <<var <<" Fibonacchi Numbers are: 1";
		
		for (int c=2; c<=var; c++)
		{
			int temp=fib;
			fib=fib+num;
			cout<<" " <<fib;
			num=temp;
		}
	}
	else
	{
		cout<<"Error: entered " <<var <<", cannot generate Fibonachi numbers";
	}
	cout<<endl;
	return 0;
}		
