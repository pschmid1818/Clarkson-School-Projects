#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
	if (argc==2)
	{	
		char *temp=argv[1];
		long int num;
		num=atol(temp);
		unsigned long int ans=1;
		
		if (num>0)
		{
			for (long int c=1;c<=num;c++)
			{
				ans=ans*c;
			}
			cout <<"Factorial(" <<num <<") = " <<ans <<endl;
		}
		else
		{
			cout<<"usage: factorial <positive_integer>\n";
		}
	}
	else
	{
		cout<<"usage: factorial <positive_integer>\n";
	}
	return 0;
}
