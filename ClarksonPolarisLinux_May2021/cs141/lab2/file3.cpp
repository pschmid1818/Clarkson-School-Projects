#include<iostream>

int main()
{
	float radius = 2.5;
	float PI = 3.141592654;

	float circumference = 2 * PI * radius;
	radius = PI * radius * radius;

	std::cout << "The radius is " << radius << std::endl;
	std::cout << "The circumference is " << circumference << std::endl;

	return 0;
}
