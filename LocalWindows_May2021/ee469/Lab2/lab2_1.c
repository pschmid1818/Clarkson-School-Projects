#include <omp.h>
#include <stdio.h>
#include <time.h>

int a[50][50];

int main()
{
	//initializing data (phase 1)
	for (int m=0;m<50;m++)
		for (int n=0;n<50;n++)
			a[m][n]=m+n;

	//sor processing (phase 2)
	int i;
	int j;

	clock_t t;							//Initilizes timer
	t = clock();							//Start timer

	#pragma omp parallel shared(a) private (i,j)
	{
		#pragma omp for schedule(dynamic, 4)
		for (i = 1; i<= 48; i++)
		{
			for (j = 1; j <=48; j++)
			{
				for (int k = 1; k <=48; k++)
				{
					a[j][k] = 2 * (a[j][k] + a[j + 1][k] + a[j - 1][k] + a[j][k + 1] + a[j][k - 1]);
				}
			}
		}
	}

	t = clock()-t;								//Stop timer
	double time = ((double)t)/CLOCKS_PER_SEC;				//Calcate timer
	printf("%f milliseconds\n", time);					//Print time

	return 0;
}
