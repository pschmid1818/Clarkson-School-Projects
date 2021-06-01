#include<iostream>
#include<cstring>
#include<vector>
#include<fstream>
#include<stdlib.h>
#include<sstream>
using namespace std;

string name();
string account();
vector<string> accountsmake();
void accountmake(vector<string> accounts, string userinfo);
void transaction(vector<string> accounts, string money, int x, string userinfo);
void accountrewrite(vector<string> accounts, string money, int x, string userinfo);
string tostring(double cash);

int main()
{
	cout <<"Login\n";
	string firstname;
	cout <<"What is your first name?\n";
	firstname=name();

	string lastname;
	cout <<"What is your last name?\n";
	lastname=name();
		
	string accountnumber;
	cout <<"What is your account number\n";
	accountnumber=account();
	
	string userinfo=firstname+" "+lastname+" "+accountnumber;

	vector<string> accounts;
	accounts=accountsmake();

	system("clear");

	int x;
	string money;
	string newaccount;
	for(int c=0; c<=accounts.size()-1; c++)
	{
		if(userinfo==accounts[c])
		{
			cout <<"Welcome " <<firstname <<" " <<lastname <<endl;
			x=c+1;
			money=accounts[x];
			transaction(accounts, money, x, userinfo);
			break;
		}
		else
		{
			cout <<"Account not detected for " <<userinfo <<". Would you like to make an account today?\nYes/No\n";
			cin >>newaccount;
			if(newaccount=="Yes" || newaccount=="Y")
			{
				accountmake(accounts, userinfo);
				break;
			}
			if(newaccount=="No" || newaccount=="N")
			{
				cout <<"Have a nice day!\n";
				break;
			}
		}
	}
	
	return 0;
}

string name()
{
	string name;
        cin >>name;

        bool check=false;

        do
        {
	
	int length=name.length();

                for(int c=0; c<=length-1; c++)
                {
                        if (name[c]=='!'||name[c]=='@'||name[c]=='#'||name[c]=='$'||name[c]=='%'||name[c]=='^'||name[c]=='&'||name[c]=='*'||name[c]=='('||name[c]==')'||name[c]=='_'||name[c]=='+'||name[c]=='-'||name[c]=='='||name[c]=='{'||name[c]=='}'||name[c]=='['||name[c]==']'||name[c]==':'||name[c]==';'||name[c]=='<'||name[c]=='>'||name[c]==','||name[c]=='.'||name[c]=='~'||name[c]=='|'||name[c]=='?'||name[c]=='1'||name[c]=='2'||name[c]=='3'||name[c]=='4'||name[c]=='5'||name[c]=='6'||name[c]=='7'||name[c]=='8'||name[c]=='9'||name[c]=='0')
                       	{
				cout <<"Error: No special characters\nTry again: ";
                		cin >>name;
			}
		}
        	if(length<2||length>10)
        	{
        	        cout <<"Error: name must be larger than 2 digits and less than 10\nTray again: ";
        		cin >>name;
		}
        	if(isupper(name[0])!=0)
        	{
			int x=0;
        	        for(int c=1; c<=length-1; c++)
			{
				if(islower(name[c])!=0)
				{
					x++;
				}
			}
        		if(x==length-1)
			{
				check=true;
			}
		}
		else
		{
			cout<<"Error: First letter must be capital, all rest must be lower.\n Try again: ";
			cin >>name;
		}
	}
	while(!check);
	
	return name;
}

string account()
{
	string acc;
	cin >>acc;
	bool check=false;

	do
	{
		if(isdigit(acc[0])!=0 && isdigit(acc[1])!=0 && isdigit(acc[2])!=0 && acc[3]=='-' && isdigit(acc[4])!=0 && isdigit(acc[5])!=0 && isdigit(acc[6])!=0 && acc[7]=='-' && isdigit(acc[8])!=0 && isdigit(acc[9])!=0 && isdigit(acc[10])!=0 && isdigit(acc[11])!=0)
		{
			check=true;
		}
		else
		{
			cout <<"Error: Account number must be in the form of xxx-xxx-xxxx\n Try again: ";
			cin >>acc;
		}	
	}
	while(!check);
	
	return acc;
}

vector<string> accountsmake()
{
	vector<string> accounts;
	string line;

	ifstream file ("accounts.txt");
	if (file.is_open())
	{
		while (getline(file,line))
		{
			accounts.push_back(line);
		}
	file.close();
	}
	
	return accounts;
}

void accountmake(vector<string> accounts, string userinfo)
{
	string money;
	cout <<"Using the info entered an account has been created.\nHow much money would you like to deposit?\n";
	cin >>money;
	
	bool check=false;
	do
	{
		if(money[0]!='-')
		{
			check=true;
		}
		else
		{
			cout <<"Error: Ammount entered cannot be negetive\n Tra again: ";
		}
	}
	while(!check);
	int x=-1;
	accountrewrite(accounts, money, x, userinfo);
	return;
}

string tostring(double cash)
{
        ostringstream money;
        money <<cash;
        return money.str();
}

void transaction(vector<string> accounts, string money, int x, string userinfo)
{
	int size=money.length()+1;
	char temp[size];
	strcpy(temp, money.c_str());
	double cash=atof(temp);
	
	double math;
	cout <<"You have $" <<cash <<" in your account.\nTo add funds put in a positive number.\nTo take funds put in a negitive number\n";
	cin >>math;

	cash=cash+math;
	
	money=tostring(cash); //c++11 is a nice thing to have

	accountrewrite(accounts, money, x, userinfo);

	return;
}

void accountrewrite(vector<string> accounts, string money, int x, string userinfo)
{
	if(x==-1)
	{
		accounts.push_back(userinfo);
		accounts.push_back(money);
	}
	else
	{
		accounts[x]=money;
	}
	
	ofstream file ("accounts.txt");
        if(file.is_open())
        {
		for(int c=0; c<=accounts.size()-1; c++)
		{
			file <<accounts[c] <<endl;
		}
	file.close();
	}

	return;
}

