#include <omp.h>
#include <stdio.h>
#include <time.h>

void smallwork()
{
}

void bigwork()
{
	unsigned long sum = 0;
	for (int i=0;i<100000000;i++)
		sum+=i;
}

int main()
{
	omp_set_dynamic(0); //disable dynamic threads
	omp_set_num_threads(8); //set the number of threads

	printf("Running...\n");

	clock_t t_less, t_mod;	//initialize clocks

	t_less = clock(); //start first clock
	#pragma omp parallel
	{
		for (int i=0;i<100;i++)	//"less than" for loop
		{
			if (i<50)
			{
				smallwork();
			}
			else
			{
				bigwork();
			}
		}
	}
	t_less = clock()-t_less; //stop first clock

	t_mod = clock(); //start second clock
	#pragma omp parallel
	{
		for (int i=0;i<100;i++) //"modulus" for loop
		{
			if (i%2)
			{
				smallwork();
			}
			else
			{
				bigwork();
			}
		}
	}
	t_mod = clock()-t_mod; //stop second clock

	double time_less = (((double)t_less)/CLOCKS_PER_SEC); //time to seconds
	double time_mod = (((double)t_mod)/CLOCKS_PER_SEC); //time to seconds 

	printf("Done!\n%f seconds for the less than for loop\n%f seconds for the modulus for loop\n\n",time_less, time_mod); //output time

	return 0;
}
