#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define MAXWORK 40
int work[MAXWORK]; // work to be done
int nwork=0; // number of items in the queue
int nextput=0; // producer will place number # at work[nextput]
int nextget=-1; // consumer will obtain next # at work[nextget]
int breaksum; // sum after which everyone stops
int done_p = 0; // value 1 signals producer exceeded breaksum
int psum,csum; // sums found by producer, consumers
int pwork; // work done by producer
int *cwork; // work done by the consumers
int nth; // number of threads
int done_c = 0; // value 1 signals consumer stops

void next(int *m)
{
    (*m)++;
    if (*m >= MAXWORK) *m = 0;
}

void putwork(int k)
{
    int put = 0;
    while (!put)
    {
        if (nwork < MAXWORK)
        {
            #pragma omp critical
            {
                work[nextput] = k;

                if (nwork == 0) nextget = nextput;

                next(&nextput);
                nwork++;
                put = 1;
            }
        }
    }
}

int getwork()
{
    int k,get=0;

    while (!get)
    {
        if (done_p && nwork == 0) return -1; //indicate termination
        #pragma omp critical
        {
            if (nwork > 0)
            {
                k = work[nextget];
                next(&nextget);
                nwork--;

                if (nwork == 0) nextget = -1;

                get = 1;
            }
        }
    }
    return k;
}

void dowork()
{
    omp_lock_t lock1;                                   //lock for producer
    omp_init_lock(&lock1);                              //initialize lock for producer
    omp_lock_t lock2;                                   //lock for consumer
    omp_init_lock(&lock2);                              //initialize lock for consumer
    omp_set_lock(&lock2);                               //locks the consumer

    #pragma omp parallel
    {
        int me = omp_get_thread_num(); // the thread number
        int num; //the random number generated for inserting in putwork

        #pragma omp single //ensure only one thread to execute this code
        {
            //finish the initial work, like memory space allocation (2 points)
            cwork = (int*) malloc(nth);
            for (int i = 1; i < nth; i++)
            {
                cwork[i] = 0;
            }
            psum = 0;
            csum = 0;
        }

        if (me == 0)                                    // thread 0 is the producer
        {
            while(psum < breaksum && pwork < MAXWORK)   //go until either psum larger than 10000 or 50 runs
            {
                omp_set_lock(&lock1);                   //lock lock for producer
                num = 500 + rand() % 499;               //The number of work generated between 500 and 999      
                putwork(num);                           //Access putwork with random number
                psum = psum + num;                      //Add num to total psum
                pwork++;                                //Add one value to pwork
                omp_unset_lock(&lock2);                 //unlock lock for consumer
            } 
        }
        else                                            // threads 1,2,3 are consumers
        {
            while(csum < breaksum && pwork < MAXWORK)   //go until csum larger than 10000 or work is done 40 times
            {
                omp_set_lock(&lock2);                   //lock lock for consumer
                if (csum>breaksum && pwork < MAXWORK)   //condition if done
                {
                    omp_unset_lock(&lock2);             //unset the lock for other consumers
                    break;                              // ignore the rest of the code
                }
                int con = getwork();                    //Value consumed from producer
                csum = csum + con;                      //Add taken num to psum
                cwork[me]++;                            //adds one value to this thread total
                
                if (csum > breaksum && pwork < MAXWORK) //condition if done
                {
                    omp_unset_lock(&lock2);             //unset the lock for the other consumers
                }
                else
                    omp_unset_lock(&lock1);             //unlock lock for producer
            }
        }
    }
}

int main()
{
    int i;
    breaksum = 10000;
    nth = 4;
    omp_set_num_threads(nth);
    dowork();
    printf("the sum from the producer: %d\n",psum);
    printf("the sum from the consumers: %d\n",csum);
    printf("# of work done by the producer: %d\n",pwork);
    printf("# of work done by consumers:\n");
    for (i = 1; i < nth; i++)
        printf("thread %d: %d\n",i,cwork[i]);
    return 0;
}
