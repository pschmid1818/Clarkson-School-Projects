#include <stdio.h>
#include <omp.h>

int main()
{
	//Initialize variables for threads
	int i;											//Iterable
	int count = 0;										//Lock counter

	//Lock initialization
	omp_lock_t lock1;									//Initialize variable
	omp_init_lock(&lock1);									//Start omp lock
	omp_set_lock(&lock1);									//Start with lock 1 locked otherwise 5 and 10 display one after another

	omp_lock_t lock2;									//Initialize vairable
	omp_init_lock(&lock2);									//Start omp lock

	//Start threads
	#pragma omp parallel private(i)
	{
		#pragma omp sections
		{
			//"Thread 2" - not always named 2
			#pragma omp section
			{
				for(i = 1; i <= 20; i++)
				{
					if(i%5 == 0)						//Only on multiple of 5
					{
						omp_set_lock(&lock1);				//Wait for the lock so that it dispalys on time
						int id = omp_get_thread_num();			//Get thread name
						printf("Thread %d: %d\n", id, i);		//Display name and i number
						count = 0;                                      //Reset the lock counter
						omp_unset_lock(&lock2);				//Unlock lock 2 to reset the cycle
					}
				}
			}

			//"Thread 1" - not always named 1
			#pragma omp section
                       	{
				for(i = 1; i <= 20; i++)
                                {
                                        if(i%5 != 0)						//Not on multiples of 5
                                        {
						omp_set_lock(&lock2);				//Wait for lock 2
						int id = omp_get_thread_num();			//Get thread name
                       	                	printf("Thread %d: %d\n", id, i);		//Display name and i value
						count++;					//Increment lock counter
						if(count == 4)					//Wait for 4 counts to run thread 2
						{
							omp_unset_lock(&lock1);              	//Unlocks lock 1 so that thread 2 can run
						}
						else						//So that thread 1 can run 4 times
						{
							omp_unset_lock(&lock2);			//Unlocks lock 2 so that thread 1 can continue to run
						}
                       	         	}
				}
			}
		}
	}

	//Un-initialize locks when done;
	omp_destroy_lock(&lock1);
	omp_destroy_lock(&lock2);
	return 0;
}
