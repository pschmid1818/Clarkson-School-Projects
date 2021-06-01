#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<cmath>

using namespace std;

enum days {mon,tue,wed,thu,fri};
float timeToInt(std::string);
void readData(string);
float workH(string,string,string,string);
float breakLength(string,string,string,string);
float overtime(string,string,string,string);
float totPay(float,float,float,float,char);
void writeData(string);

struct Person
{
	string firstname;
	string middlename;
	string lastname;
};

struct wage 
{
	float wagePH;
	float overRate;
	char over;
};

struct timecard 
{
	float workH;
	float lunchL;
	float overTH;
	float totPay;
};

struct employee 
{
	Person empName;
	Person manag;
	wage empWage;
	timecard timeC[5];
	timecard week;
	string dept;
};

employee emp[20];

int main()
{
	string inputf;
	cout << "Enter a file name:" << endl;
	cin >> inputf;
	readData(inputf);
	cout << "Enter a file name to write:" << endl;
	cin >> inputf;
	writeData(inputf);
	return 0;
}
float timeToInt(string timeInString)
{
	int locOfDivider=timeInString.find(':');
	string timeHours=timeInString.substr(0, locOfDivider);
	string timeMins=timeInString.substr(locOfDivider+1, timeInString.length());
	float timeHoursInt;
	istringstream(timeHours) >> timeHoursInt;
	float timeMinsInt;
	istringstream(timeMins) >> timeMinsInt;
	return timeHoursInt+(timeMinsInt/60);
}

float workH(string clockIn, string lunchIn, string lunchOut, string clockOut)
{
	return (timeToInt(clockOut)-timeToInt(clockIn))-(timeToInt(lunchOut)-timeToInt(lunchIn));
}

float breakLength(string clockIn,string lunchIn, string lunchOut, string clockOut)
{
	return timeToInt(lunchOut)-timeToInt(lunchIn);
}

float overtime(string clockIn,string lunchIn, string lunchOut, string clockOut)
{
	float hoursPerDay = (timeToInt(clockOut)-timeToInt(clockIn))-(timeToInt(lunchOut)-timeToInt(lunchIn));
	if (hoursPerDay > 7.5)
	{
		return hoursPerDay-7.5;
	}
	else
	{
		return 0;
	}
}

float totPay(float workH,float overTH,float wagePH, float overRate, char over)
{
	if(over == 'Y')
	{
		return (7.5*wagePH)+(overTH*wagePH*overRate);
	}
	else if (over == 'N')
	{
		return workH*wagePH;
	}
	else 
	{
		return -1;
	}
}

void readData(string userFile)
{
	ifstream inputhandler;
	inputhandler.open(userFile.c_str());
	int x=0;
	string endtime;
	while(x<20)
	{
		string starttime;
		string lunchstart;
		string lunchend;
		emp[x].week.totPay=0;
		emp[x].week.overTH=0;
		emp[x].week.lunchL=0;
		emp[x].week.workH=0;
		for(int y=0;y<5;y++)
		{
			inputhandler>>emp[x].empWage.wagePH>>emp[x].empWage.over>>emp[x].empWage.overRate>>emp[x].empName.firstname>>emp[x].empName.middlename>>emp[x].empName.lastname>>emp[x].dept>>emp[x].manag.firstname>>emp[x].manag.middlename>>emp[x].manag.lastname>>starttime>>lunchstart>>lunchend>>endtime;
			emp[x].timeC[y].workH=workH(starttime,lunchstart,lunchend,endtime);
			emp[x].timeC[y].lunchL=breakLength(starttime,lunchstart,lunchend,endtime);
			emp[x].timeC[y].overTH=overtime(starttime,lunchstart,lunchend,endtime);
			emp[x].timeC[y].totPay=totPay(emp[x].timeC[y].workH,emp[x].timeC[y].overTH,emp[x].empWage.wagePH,emp[x].empWage.overRate,emp[x].empWage.over);
			emp[x].week.totPay+=emp[x].timeC[y].totPay;
			emp[x].week.workH+=emp[x].timeC[y].workH;
			emp[x].week.overTH+=emp[x].timeC[y].overTH;
			emp[x].week.lunchL+=emp[x].timeC[y].lunchL;
		}
		x++;
	}
	inputhandler.close();
}

void writeData(string userFile) 
{
	if (userFile.substr( userFile.size()-4) != string(".xml")) 
	{
		return;
	}
	ofstream outputhandler;
	outputhandler.open(userFile.c_str());
	int x=0;
	outputhandler<<"<payroll>\n";
	while(x<20) 
	{
		outputhandler<<"   <employee>\n      <name>"<< emp[x].empName.firstname<<" "<<emp[x].empName.middlename<<" "<<emp[x].empName.lastname<<"</name>\n";
		outputhandler<<"      <manager>"<< emp[x].manag.firstname<<" "<<emp[x].manag.middlename<<" "<<emp[x].manag.lastname<<"</manager>\n";
		outputhandler<<"      <dept>"<<emp[x].dept<<"</dept>\n      <payrate>";
		outputhandler<<emp[x].empWage.wagePH<<"</payrate>\n      <overtime>";
		if(emp[x].empWage.over=='Y') 
		{
			outputhandler<<"Yes";
		}
		else 
		{
			if(emp[x].empWage.over=='N')
		{
		outputhandler<<"No";
	}
	else
	{
		outputhandler<<"error";
	}
}
		outputhandler<<"</overtime>\n      <multiplier>"<< emp[x].empWage.overRate << "</multiplier>\n      <hours>"<<emp[x].week.workH <<"</hours>\n      <overhours>";
		outputhandler<< emp[x].week.workH-37.5 <<"</overhours>\n      <lunch>"<<emp[x].week.lunchL<<"</lunch>\n      <pay>"<< emp[x].week.totPay <<"</pay>\n   </employee>\n";
		x++;
	}
	outputhandler<<"</payroll>";
	outputhandler.close();
}

