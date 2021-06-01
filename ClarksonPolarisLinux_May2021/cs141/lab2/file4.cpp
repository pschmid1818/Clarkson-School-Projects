#include<iostream>

int main()
{
	float usPopulation = 321418821;
	float worldPopulation = 7.5E9;
	float usWorldRatio = usPopulation / worldPopulation;	

	std::cout << "The US population is " << usWorldRatio*100 << "% of the world population." << std::endl; 

	return 0;
}
