#include<iostream>
#include<cstring>
#include<locale>
#include<vector>
#include<fstream>
using namespace std;

string name();
string state();
string zipcode();
string phone();

int main()
{
	cout <<"What is your first name?\n";
	string firstname;
	firstname=name();

	cout <<"What is your middle name?\n(Note:type 'none' to opt out)\n";
	string middlename;
	middlename=name();
	
	cout <<"What is your last name?\n";
        string lastname;
        lastname=name();

	string code;
	code=state();

	string zip;
	zip=zipcode();	
	
	string phonenumber;
	phonenumber=phone();

	cout <<firstname <<" " <<middlename <<" " <<lastname <<", " <<code <<" " <<zip <<" " <<phonenumber <<endl;
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
        	else if(name=="none")
        	{
        	        name="";
        		check=true;
		}
        	else
        	{
        	        check=true;
        	}
	}
	while(!check);
	
	return name;
}

string state()
{
	cout <<"What is your state code (ex. NY)\n";
	string state;
	cin >>state;
	bool sheck=false;

	do
	{
		int length=state.length();
		if(length==2)
		{
			char t1=state[0];
			char t2=state[1];
			locale loc;
			if(isupper(t1,loc) && isupper(t2,loc))
			{
				sheck=true;
			}
			else
			{
				cout <<"Error: must be uppercase\nTry again: ";
				cin >>state;
			}
		}
		else
		{
			cout <<"Error: length must be 2 characters\nTry again: ";
			cin >> state;
		}
	}
	while(!sheck);

	return state;
}

string zipcode()
{
	string zip;
	cout <<"What was your zipcode?\n";
	cin >>zip;
	vector<string> test;
	bool zheck=false;
	string line;
	
	ifstream file ("zipcodes.txt");
	if (file.is_open())
	{
		while (getline(file,line))
		{
			test.push_back(line);
		}
	file.close();
	}
	string testzip;
	do
	{
	testzip=zip.substr(0,3);
		for(int c=0; c<=test.size()-1; c++)
		{
			if(strcmp(test[c].c_str(),testzip.c_str())!=0)
			{
				zheck=true;
				break;
			}
		
		}
		if(zheck==false)
		{
			cout <<"Error: Zipcode not recognized\nTry again: ";
			cin >>zip;		
		} 
	}
	while(!zheck);

	return zip;
}

string phone()
{
	string phone;
	cout <<"What is your phone number?\n";
	cin >>phone;
	bool pheck=false;

	do
	{
		if(phone[0]=='(' && isdigit(phone[1])!=0 && isdigit(phone[2])!=0 && isdigit(phone[3])!=0 && phone[4]==')' && phone[5]=='-' && isdigit(phone[6])!=0 && isdigit(phone[7])!=0 && isdigit(phone[8])!=0 && phone[9]=='-' && isdigit(phone[10])!=0 && isdigit(phone[11])!=0 && isdigit(phone[12])!=0 && isdigit(phone[13])!=0)
		{
			pheck=true;
		}
		if(isdigit(phone[0])!=0 && isdigit(phone[1])!=0 && isdigit(phone[2])!=0 && phone[3]=='-' && isdigit(phone[4])!=0 && isdigit(phone[5])!=0 && isdigit(phone[6])!=0 && phone[7]=='-' && isdigit(phone[8])!=0 && isdigit(phone[9])!=0 && isdigit(phone[10])!=0 && isdigit(phone[11])!=0)
		{
			pheck=true;
		}
		else
		{
			cout <<"Error: Not a recognized phone format\nTry again: ";
			cin >>phone;
		}
	}
	while(!pheck);
	return phone;
}
	
	
