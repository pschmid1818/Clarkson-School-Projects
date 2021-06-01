#include<iostream>   // allows basic input and output
using namespace std; // So I dont need to type std::

int main()
{
	// Initialize weighted variables
	float homeworkWeight=.25; // 25% of grade
	float examWeight=.35;     // 35% of grade
	float finalWeight=.40;    // 40% of grade

	float homeworkScore=92;   // Stuart Little's homework grade
	float examScore=93;       // Stuart Little's exam grade
	float finalScore=94;      // Stuart Little's final grade

	float classScore=(homeworkScore*homeworkWeight)+(examWeight*examScore)+(finalWeight*finalScore);
	// Calculates Stuart Little's class grade
	
	cout<<"Final Grade " <<classScore <<endl;
	// Output Stuart Little's final grade

	return 42;
}
