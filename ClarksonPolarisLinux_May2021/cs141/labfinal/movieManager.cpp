#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>

using namespace std;

void showall();
void stats();

struct movie
{
	string moviename;
	int year;
	float gross;
};

movie allmovies[51];

int main()
{
	ifstream file;
	string nametemp;
	int yeartemp;
	float grosstemp;
	
	file.open("moviedata.txt");
	
	while(file.is_open())
	{
		for(int c=0; c<=50; c++)
		{
        		file >>nametemp >>yeartemp >>grosstemp;
			allmovies[c].moviename=nametemp;
			allmovies[c].year=yeartemp;
			allmovies[c].gross=grosstemp;
		}
	file.close();
	}
	
	string x;
	cout <<"What would you like to do?\nSee all movies (all)\nSee statistics by year (stats)\nQuit (quit)" <<endl;
	
	bool check=false;
	
	while(check==false)
	{
		cin >>x;
		system("clear");
		if(x=="all")
		{
			showall();
		}
		if(x=="stats")
		{
			cout <<"What years movies?\n";
			stats();
		}
		if(x=="quit")
		{
			check=true;
		}
		if(x!="all" && x!="stats" && x!="quit")
		{
			cout <<"Error: not a given command\nTry again: ";	
		}
		cout <<"(all)(stats)(quit)\n";
	}
	
	system("clear");
	return 0;
}

void showall()
{
	
        for(int c=0; c<=50; c++)
        {
                cout <<allmovies[c].moviename <<" released in " <<allmovies[c].year <<endl;
        }
	return;
}

void stats()
{
	int useryear;
	cin >>useryear;
	bool check=false;
	while(check==false)
	{
		for(int c=0; c<=50; c++)
		{
			if(allmovies[c].year==useryear)
			{
				cout <<allmovies[c].moviename <<" made $" <<allmovies[c].gross <<endl;
				check=true;
			}
			if(check==false)
			{
				cout<<"Error: Movies did not exist then\nTry again: ";
				cin >>useryear;
			}
				
		}
	}
	
	return;
}

