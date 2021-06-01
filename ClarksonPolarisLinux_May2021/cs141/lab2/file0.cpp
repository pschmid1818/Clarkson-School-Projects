#include<iostream>

int main()
{
	int numBananas = 5;
	int numApples = 10;	

	int totalFruits = numBananas + numApples;

	numBananas = 20;
	numApples = 5;

	totalFruits = numBananas + numApples; 

	std::cout << "Total fruits = " << totalFruits << std::endl;
	
	return 0;
}
