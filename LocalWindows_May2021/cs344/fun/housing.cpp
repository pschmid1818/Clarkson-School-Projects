#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

int roll(vector<int> used)
{
    int num = 0;

    bool test = false;
    do
    {
        num = rand() % 6 + 1;

        for(int i = 0; i < used.size(); i++)
        {
            if (num =! used[i])
            {
                test = true;
            }
        } 
    }
    while(test = false);


    return num;
}

void housing()
{
    string name1;
    string name2;
    string name3;
    string name4;
    string name5;
    string name6;
    vector<int> temp;
    temp.push_back(0);
    vector<int> used;
    int num;

    cout <<"Name 1: ";
    cin >>name1;
    cout <<"Name 2: ";
    cin >>name2;
    cout <<"Name 3: ";
    cin >>name3;
    cout <<"Name 4: ";
    cin >>name4;
    cout <<"Name 5: ";
    cin >>name5;
    cout <<"Name 6: ";
    cin >>name6;

    num = roll(temp);
    cout <<"In housing: " <<num <<endl;
    used.push_back(num);
    
    num = roll(used);
    cout <<num <<endl;
    used.push_back(num);

    num = roll(used);
    cout <<num <<endl;
    used.push_back(num);

    num = roll(used);
    cout <<num <<endl;
    used.push_back(num);

    num = roll(used);
    cout <<num <<endl;
    used.push_back(num);

    num = roll(used);
    cout <<num <<endl;
    used.push_back(num);

    for (int i = 0; i <= 6; i++)
    {
        if (used[i] == 1)
        {
            cout << name1 <<endl;
        }
        else if (used[i] == 2)
        {
            cout << name2 <<endl;
        }
        else if (used[i] == 3)
        {
            cout << name3 <<endl;
        }
        else if (used[i] == 4)
        {
            cout << name4 <<endl;
        }
        else if (used[i] == 5)
        {
            cout << name5 <<endl;
        }
        else if (used[i] == 6)
        {
            cout << name6 <<endl;
        }
    }
}

int main()
{
    housing();

    return 0;
}