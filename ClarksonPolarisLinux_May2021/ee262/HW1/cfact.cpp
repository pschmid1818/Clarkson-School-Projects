#include<iostream>
using namespace std;

int main()
{
	int fact,ans;
	cout<<"Enter an integer larger than 1: ";
	cin>>fact;
	
	if (fact<=0)
	{
		cout<<"Error: Number must be larger than 1\n";
		return 0;
	}
	else
	{
		cout<<"Factrors of " <<fact <<": ";

		for (int c=1;c<fact;c++)
		{
			ans=fact%c;
			if (ans==0)
			{
				cout<<c <<", ";
			}
		}	
	}
	cout<<fact <<endl;
	return 0;
}
