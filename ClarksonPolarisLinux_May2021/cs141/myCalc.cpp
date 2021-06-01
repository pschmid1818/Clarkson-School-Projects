#include<iostream>
#include<string.h>
#include<cmath>
using namespace std;

int main()
{
int num1,num2,ans;
string op;
cout<<"Enter a number, an operation, and a number.\nex. 2 + 2\n";

cin>>num1 >>op >>num2;

if (op=="add" || op=="+")
{
	ans=num1+num2;
	cout<<num1 <<" " <<op <<" " <<num2 <<" is " <<ans <<endl;
}
if (op=="subtract" || op=="-")
{
	ans=num1-num2;
	cout<<num1 <<" " <<op <<" " <<num2 <<" is " <<ans <<endl;
}
if (op=="multiply" || op=="*")
{
	ans=num1*num2;
	cout<<num1 <<" " <<op <<" " <<num2 <<" is " <<ans <<endl;
}
if (op=="divide" || op=="/")
{
	if (num2==0)
	{
		cout<<"Haha, nice try. I'm not letting you brick a computer today.\n";
		return 0;
	}
	else
	{
		ans=num1/num2;
		cout<<num1 <<" " <<op <<" " <<num2 <<" is " <<ans <<endl;
	}
}
if (op=="power" || op=="^")
{
	ans=pow(num1,num2);
	cout<<num1 <<" " <<op <<" " <<num2 <<" is " <<ans <<endl;
}
if (op=="mod" || op=="%")
{
	ans=num1%num2;
	cout<<num1 <<" " <<op <<" " <<num2 <<" is " <<ans <<endl;
}	
return 0;
}
