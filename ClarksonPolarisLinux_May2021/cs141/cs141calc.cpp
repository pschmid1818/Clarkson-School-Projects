#include<iostream>
#include"string.h"
using namespace std;

void work();

int main()
{
	work();
}

void work()
{
	float numOne,numTwo,ans;
	string opp;

	cout<<"Enter '-1 -1 quit' or '-1 -1 x' to exit\n";
	cin >>numOne >>numTwo >>opp;

	if (opp=="quit" || opp=="x")
	{
		if (numOne==-1 && numTwo==-1)
		{
			cout<<"Have a nice day!\n";
			return;
		}
		else
		{
			cout<<"Error: Illegal Exit Values\n";
			work();
		}
	}
	if (opp=="plus" || opp=="+")
	{
		ans=numOne+numTwo;
		cout<<"Result of " <<numOne <<" " <<numTwo <<" " <<"Plus is " <<ans <<endl;
		work();
	}
	if (opp=="minus" || opp=="-")
	{
		ans=numOne-numTwo;
		cout<<"Result of " <<numOne <<" " <<numTwo <<" " <<"Minus is " <<ans <<endl;
		work();
	}
	if (opp=="multiply" || opp=="*")
	{	
		ans=numOne*numTwo;
		cout<<"Result of " <<numOne <<" " <<numTwo <<" " <<"Multiply is " <<ans <<endl;
		work();
	}
	if (opp=="divide" || opp=="/")
	{
		if (numTwo==0)
		{
			cout<<"Error: Divide by Zero\n";
			work();
		}
		else
		{
			ans=numOne/numTwo;
			cout<<"Result of " <<numOne <<" " <<numTwo <<" " <<"Divide is " <<ans <<endl;
			work();
		}			
	}
}
