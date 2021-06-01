#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>

using namespace std;

void ai(vector<string> board);
void pvp(vector<string> board);
bool wincheck(vector<string> board);
void output(vector<string> board);
int aiskill(vector<string> board);

//I didnt see part of my grade was dependant on on a struct until after I completed the function and rechecked the instructions
//This is what I thought of to add a useful struct used everytime, the struct will start the entire game every time

struct question
{
	string out;
	string commands;
	string in; 
};

int main()
{
	vector<string> board;
	bool cc;
	bool ca; //both are checks to make sure commands are correct

	while(1==1)
	{	
		system("clear");

		//creates a blank board

		for(int c=0; c<=8; c++)
        	{
        	        board.push_back("0");
        	}
        	board[0]="1";
        	board[1]="2";
        	board[2]="3";
        	board[3]="4";
        	board[4]="5";
        	board[5]="6";
        	board[6]="7";
        	board[7]="8";
        	board[8]="9";
		
		//starts the game by asking what type of game you want to play using the struct, first check is used to verify a command string based choices are given like this (command)
		//goes to ai or player game voids
		
		question start;
		start.out="Welcome to Tic Tac Toe\n";
		start.commands="Will you be playing against another player(player) or agaist an ai(ai)?\n";
        	
		cout <<start.out <<start.commands;
        	cin >>start.in;
		
        	cc=false;
		while(cc==false)
        	{
                	if(start.in=="player")
                	{
                	        pvp(board);
                        	cc=true;
                	}
                	if(start.in=="ai")
                	{
                	        ai(board);
                	        cc=true;
                	}
                	if(start.in!="ai" && start.in!="player")
                	{
                	        cout <<"Error: Not a recognized gamemode\n";
                	        cin >>start.in;
                	}
        	}

		//lets the game start again or end using the struct, second check is used to verify commands
		//(commands) are given in the same way
		
		question again;
		again.out="Would you like to play again?\n";        	
		again.commands="(yes)(no)\n";
        	cout <<again.out <<again.commands;
		cin >>again.in;
        	ca=false;
		while(ca==false)
		{
			if(again.in=="yes")
        		{
        			ca=true; 
        		}
        		if(again.in=="no")
        		{
				system("clear");
				cout <<"Have a nice day!\n";
        		        return 0;
        		}
			if(again.in!="yes" && again.in!="no")
			{
				cout <<"Error: not a recognized command\nTry again: ";
				cin >>again.in;
			}
		}
	}
}

//player vs player game
//entire game is in a recursive loop that only ends when one of the win conditions are met
//win condition is checked in a later function

void pvp(vector<string> board)
{
	output(board);
	
	bool win=false;
	int x;

	while(1==1)
	{
	
		//player 1's turn	

		cout<<"Player 1's turn\nWhich spot will you take (1-9)\n";
		cin >>x;
		while(x>9 || x<1 || board[x-1]=="X" || board[x-1]=="O")
		{
			cout <<"Error: move is illegal\nTry again: ";
			cin >>x;
		}
		board[x-1]="X";
		output(board);
		win=wincheck(board);
		if(win==true)
		{	
			break;
		}
 
		//player 2's turn

		output(board);
		cout<<"Player 2's turn\nWhich spot will you take (1-9)\n";
		cin >>x;
		while(x>9 || x<1 || board[x-1]=="X" || board[x-1]=="O")
		{
			cout <<"Error: move is illegal\nTr again: ";
			cin >>x;
		}
		board[x-1]="O";
		output(board);
		win=wincheck(board);
		if(win==true)
		{
			break;
		}
	}
	return;
}

//player vs ai game
//player turn is the same as in pvp() but ai doesn't have the same checks, aiskill() details how it works
//win condition will be the same

void ai(vector<string> board)
{
	output(board);

        bool win=false;
        int x;

        while(1==1)
        {
                cout<<"Player 1's turn\nWhich spot will you take (1-9)\n";
                cin >>x;
                while(x>9 || x<1 || board[x-1]=="X" || board[x-1]=="O")
                {
                        cout <<"Error: move is illegal\nTry again: ";
                        cin >>x;
                }
                board[x-1]="X";
                output(board);
                win=wincheck(board);
                if(win==true)
                {
                        break;
                }

		x=aiskill(board);
                board[x-1]="O";
                output(board);
                win=wincheck(board);
                if(win==true)
                {
                        break;
                }
	}

	return;
}

//outputs the board and clears the screen

void output(vector<string> board)
{
	system("clear");
        cout <<board[0] <<"|" <<board[1] <<"|" <<board[2] <<endl <<"-----" <<endl;
        cout <<board[3] <<"|" <<board[4] <<"|" <<board[5] <<endl <<"-----" <<endl;
        cout <<board[6] <<"|" <<board[7] <<"|" <<board[8] <<endl;
	return;
}

//anytime the vector has 3 X's or O's the win bool is checked

bool wincheck(vector<string> board)
{
	bool win=false;

	//player 1 winning

	if(board[0]=="X" && board[1]=="X" && board[2]=="X")
	{
		win=true;
		cout <<"Player 1 wins\n";
	}
	if(board[3]=="X" && board[4]=="X" && board[5]=="X")
	{
		win=true;
		cout <<"Player 1 wins\n";
	}
	if(board[6]=="X" && board[7]=="X" && board[8]=="X")
	{
		win=true;
		cout <<"Player 1 wins\n";
	}
	if(board[0]=="X" && board[3]=="X" && board[6]=="X")
	{
		win=true;
		cout <<"Player 1 wins\n";
	}
	if(board[1]=="X" && board[4]=="X" && board[7]=="X")
	{
		win=true;
		cout <<"Player 1 wins\n";
	}
	if(board[2]=="X" && board[5]=="X" && board[8]=="X")
	{
		win=true;
		cout <<"Player 1 wins\n";
	}
	if(board[2]=="X" && board[4]=="X" && board[6]=="X")
	{
		win=true;
		cout <<"Player 1 wins\n";
	}
	if(board[0]=="X" && board[4]=="X" && board[8]=="X")
	{
		win=true;
		cout <<"Player 1 wins\n";
	}

	//player 2 winning

	if(board[0]=="O" && board[1]=="O" && board[2]=="O")
        {
                win=true;
        	cout <<"Player 2 wins\n";
	}
        if(board[3]=="O" && board[4]=="O" && board[5]=="O")
        {
                win=true;
        	cout <<"Player 2 wins\n";
	}
        if(board[6]=="O" && board[7]=="O" && board[8]=="O")
        {
                win=true;
        	cout <<"Player 2 wins\n";
	}
        if(board[0]=="O" && board[3]=="O" && board[6]=="O")
        {
                win=true;
        	cout <<"Player 2 wins\n";
	}
        if(board[1]=="O" && board[4]=="O" && board[7]=="O")
        {
                win=true;
        	cout <<"Player 2 wins\n";
	}
        if(board[2]=="O" && board[5]=="O" && board[8]=="O")
        {
                win=true;
        	cout <<"Player 2 wins\n";
	}
        if(board[2]=="O" && board[4]=="O" && board[6]=="O")
        {
                win=true;
		cout <<"Player 2 wins\n";
	}
	if(board[0]=="O" && board[4]=="O" && board[8]=="O")
        {
                win=true;
        	cout <<"Player 2 wins\n";
	}

	if(board[0]!="1" && board[1]!="2" && board[2]!="3" && board[3]!="4" && board[4]!="5" && board[5]!="6" && board[6]!="7" && board[7]!="8" && board[8]!="9")
	{
		cout<<"It's a tie\n";
		win=true;
	}

	return win;	
}


//The ai is all contained in this function
//it first selects a random spot to pick
//if two X's are detected in a row it places the O in responce in the "ai trying not to lose" section
//further down is the exact opposite if there are two O's place the third in the "ai trying to win" section

int aiskill(vector<string> board)
{
	int x;
	x=rand() % 9 + 1;
	if(board[x-1]=="X" || board[x-1]=="O")
	{
		x=rand() % 9 + 1;
	}

	//ai trying not to lose
	
	if(board[0]=="X" && board[1]=="X" && board[2]=="3")
        {
              	x=3;
        }
	if(board[0]=="X" && board[1]=="2" && board[2]=="X")
        {
                x=2;
        }
	if(board[0]=="1" && board[1]=="X" && board[2]=="X")
        {
                x=1;
        }
	
	if(board[3]=="X" && board[4]=="X" && board[5]=="6")
        {
                x=6;
        }
        if(board[3]=="X" && board[4]=="5" && board[5]=="X")
        {
                x=5;
        }
        if(board[3]=="4" && board[4]=="X" && board[5]=="X")
        {
                x=4;
        }

	if(board[6]=="X" && board[7]=="X" && board[8]=="9")
        {
                x=9;
        }
        if(board[6]=="X" && board[7]=="8" && board[8]=="X")
        {
                x=8;
        }
        if(board[6]=="7" && board[7]=="X" && board[8]=="X")
        {
                x=7;
        }

	if(board[0]=="X" && board[3]=="X" && board[6]=="7")
        {
                x=7;
        }
        if(board[0]=="X" && board[3]=="4" && board[6]=="X")
        {
                x=4;
        }
        if(board[0]=="1" && board[3]=="X" && board[6]=="X")
        {
                x=1;
        }

	if(board[1]=="X" && board[4]=="X" && board[7]=="8")
        {
                x=8;
        }
        if(board[1]=="X" && board[4]=="5" && board[7]=="X")
        {
                x=5;
        }
        if(board[1]=="2" && board[4]=="X" && board[7]=="X")
        {
                x=2;
        }

	if(board[2]=="X" && board[5]=="X" && board[8]=="9")
        {
                x=9;
        }
        if(board[2]=="X" && board[5]=="6" && board[8]=="X")
        {
                x=6;
        }
        if(board[2]=="3" && board[5]=="X" && board[8]=="X")
        {
                x=3;
        }

	if(board[2]=="X" && board[4]=="X" && board[6]=="7")
        {
                x=7;
        }
        if(board[2]=="X" && board[4]=="5" && board[6]=="X")
        {
                x=5;
        }
        if(board[2]=="3" && board[4]=="X" && board[6]=="X")
        {
                x=3;
        }

	if(board[0]=="X" && board[4]=="X" && board[8]=="9")
        {
                x=9;
        }
        if(board[0]=="X" && board[4]=="5" && board[8]=="X")
        {
                x=5;
        }
        if(board[0]=="1" && board[4]=="X" && board[8]=="X")
        {
                x=1;
        }

	//ai trying to win

	if(board[0]=="O" && board[1]=="O" && board[2]=="3")
        {
              	x=3;
        }
	if(board[0]=="O" && board[1]=="2" && board[2]=="O")
        {
                x=2;
        }
	if(board[0]=="1" && board[1]=="O" && board[2]=="O")
        {
                x=1;
        }
	
	if(board[3]=="O" && board[4]=="O" && board[5]=="6")
        {
                x=6;
        }
        if(board[3]=="O" && board[4]=="5" && board[5]=="O")
        {
                x=5;
        }
        if(board[3]=="4" && board[4]=="O" && board[5]=="O")
        {
                x=4;
        }

	if(board[6]=="O" && board[7]=="O" && board[8]=="9")
        {
                x=9;
        }
        if(board[6]=="O" && board[7]=="8" && board[8]=="O")
        {
                x=8;
        }
        if(board[6]=="7" && board[7]=="O" && board[8]=="O")
        {
                x=7;
        }

	if(board[0]=="O" && board[3]=="O" && board[6]=="7")
        {
                x=7;
        }
        if(board[0]=="O" && board[3]=="4" && board[6]=="O")
        {
                x=4;
        }
        if(board[0]=="1" && board[3]=="O" && board[6]=="O")
        {
                x=1;
        }

	if(board[1]=="O" && board[4]=="O" && board[7]=="8")
        {
                x=8;
        }
        if(board[1]=="O" && board[4]=="5" && board[7]=="O")
        {
                x=5;
        }
        if(board[1]=="2" && board[4]=="O" && board[7]=="O")
        {
                x=2;
        }

	if(board[2]=="O" && board[5]=="O" && board[8]=="9")
        {
                x=9;
        }
        if(board[2]=="O" && board[5]=="6" && board[8]=="O")
        {
                x=6;
        }
        if(board[2]=="3" && board[5]=="O" && board[8]=="O")
        {
                x=3;
        }

	if(board[2]=="O" && board[4]=="O" && board[6]=="7")
        {
                x=7;
        }
        if(board[2]=="O" && board[4]=="5" && board[6]=="O")
        {
                x=5;
        }
        if(board[2]=="3" && board[4]=="O" && board[6]=="O")
        {
                x=3;
        }

	if(board[0]=="O" && board[4]=="O" && board[8]=="9")
        {
                x=9;
        }
        if(board[0]=="O" && board[4]=="5" && board[8]=="O")
        {
                x=5;
        }
        if(board[0]=="1" && board[4]=="O" && board[8]=="O")
        {
                x=1;
        }	

	return x;	
}
