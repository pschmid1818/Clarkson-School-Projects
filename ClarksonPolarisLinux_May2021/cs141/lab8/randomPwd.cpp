#include<iostream>
#include<cstring>
#include<vector>
#include<fstream>
#include<cstdlib>
using namespace std;

vector<string> namemake();
vector<string> keymake();
vector<string> fusion(vector<string> keys, vector<string> names);
void output(vector<string> secure);

int main()
{
	srand(time(0));
	vector<string> names;
	names=namemake();

	vector<string> keys;
	keys=keymake();

	vector<string> secure;
	secure=fusion(keys, names);	

	output(secure);

	return 0;
}

vector<string> namemake()
{
	vector<string> names;
        string line;
        
	ifstream employees("employees.txt");
        
	if(employees.is_open())
        {
                while(getline(employees,line))
                {
                        names.push_back(line);
                }
                employees.close();
        }
        return names;
}

vector<string> keymake()
{
        vector<string> keys;
        string line;
        ifstream passwords("passwords.txt");
        if(passwords.is_open())
        {
                while(getline(passwords,line))
                {
                        keys.push_back(line);
                }
                passwords.close();
        }
	return keys;
}

vector<string> fusion(vector<string> keys, vector<string> names)
{
	for (int c=0; c<=49; c++) 
	{
		int x = rand()%50;
		string rand = keys[x];
		keys[x]=keys[c];
		keys[c]=rand; 
		
		
	}

	vector<string> secure;
	for(int c=0; c<=49; c++)
	{
		string x=names[c]+" "+keys[c];
		secure.push_back(x);
	}

	for(int c=0; c<=49; c++)
	{
		cout <<secure[c] <<endl;
	}
	return secure;
	
}  

void output(vector<string> secure)
{
	ofstream output;
	output.open("empPasswords.txt");
	for (int c=0; c<=49; c++)
	{
		output <<secure[c] <<endl;
	}
	output.close();

	return;	
}
