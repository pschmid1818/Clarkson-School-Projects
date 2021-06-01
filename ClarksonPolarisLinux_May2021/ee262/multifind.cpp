#include<iostream>
#include<string.h>
using namespace std;

int main()
{
	string myStr="the quick brown fox jumped right over the lazy dog.";
	
	cout<<"Enter a word or string: ";
	string find;
	cin>>find;
	int error;
	for (int c=0; c < myStr.length(); c++)
	{
		if (myStr.substr(c,find.length())==find)
		{
			cout<<c <<", ";
			error++;
		}
	}
	if (error==0)
	{
		cout<<"Not found";
	}

	cout<<endl;	
	return 0;
}

