#include<iostream>
#include<cstring>
using namespace std;

bool isPalindrome(string strinput);

int main(int cllength, char *clinput[])
{	
	const char* input=clinput[cllength-1]; 
		
	string strinput(input);
	bool ans;
	ans=isPalindrome(strinput);

	if (ans==1)
	{
		cout <<"is a palindrome\n";
	}
	else if (ans==0)
	{
		cout <<"not a palindrome\n";
	}

	return 0;
}

bool isPalindrome(string strinput)
{
	int length=strinput.length();
	string test=strinput;
	bool ans;
	
	for (int c=length-1; c>=0; c--)
	{
		test[length-1-c]=strinput[c];
	}
	if (test==strinput)
	{
		ans=1;
	}
	else
	{
		ans=0;	
	}
	return ans;
}	
