#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

int main()
{
	string input;
	string str;
	cout <<"Enter a phrase\n";
	getline(cin,input);
	int length=input.length();
	
	vector<string> v;
	
	for (int c=0; c<length; c++)
	{
		if ((input[c]=='.'||input[c]=='?'||input[c]=='!'||input[c]==',') && input[c+1]==' ')
		{
			c++;
		}
		if (input[c]==' '||input[c]=='.'||input[c]=='?'||input[c]=='!'||input[c]==',')
		{
			v.push_back(str);
			str.clear();
			c++;
		}
		str=str+input[c];
	}
	
	for (int c=0; c<v.size(); c++)
	{
		bool test=false;
		int points=0;
		for(int x=0; x<c; x++)
		{	
			if (v[c]==v[x])
			{
				test=true;
			}
		}
		
		for (int x=c; x<v.size(); x++)
		{
			if (v[c]==v[x] && !test)
			{
				points++;
			}
		}
		
		if (points>=1)
		{
			cout <<v[c] <<":";
			for (int y=0; y<points; y++)
			{
				cout <<"*";
			}
			cout <<"\n";
		}	
	}
	return 0;
}


