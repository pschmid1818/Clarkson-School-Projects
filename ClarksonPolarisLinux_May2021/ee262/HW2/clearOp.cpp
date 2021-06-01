#include <iostream>
#include <cstring>
using namespace std;
int main(int argc, char *argv[]) 
{
	if (argc != 2) 
	{
	cout<<"usage: clearOp a_string"<<endl;
	return 1;
	}
	
	char* argvch=argv[argc-1];
	string argvstr(argvch);
	int slen = argvstr.length();
	char* str = new char[slen];
	
	for (int i=slen-1; i>=0; i--) 
	{
		str[slen-1-i]=argvstr[i];
	}

	cout <<str <<endl;
	return 0;
}

