#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread1(void *);
void *thread2(void *);

char *p; 
//pthread_mutex_t lock;                           //timing lock

int main(void)
{
    pthread_t t_a;
    pthread_t t_b;

    p = (char*) malloc(sizeof(char) * (12));    //allocate space for p
    p[0] = 'c';                                 //Set the values for 0 to 7
    p[1] = 'l';
    p[2] = 'a';
    p[3] = 'r';
    p[4] = 'k';
    p[5] = 's';
    p[6] = 'o';
    p[7] = 'n';

   

    pthread_create(&t_a,NULL,thread2,(void *)NULL);
    pthread_create(&t_b,NULL,thread1,(void *)NULL);
    pthread_join(t_b, NULL);
    free(p);
    exit(0);
}

void *thread1(void *junk)
{
    
    //pthread_mutex_unlock(&lock);                //unlock so thread2 can start
    for(int i = 8; i <= 10; i++)                //for index 8 to 10
    {
        p[i] = '3';                             //change p's index to '3'
    }
    
    printf("%s\n", p);                          //print p
    
    sleep(10);                                  //sleep for 10 seconds

    printf("%s\n", p);                          //print p
    
}

void *thread2(void *junk)
{
    //pthread_mutex_lock(&lock);                  //makes sure thread 1 starts first
    sleep(3);                                   //sleep for 3 seconds
    for(int i = 8; i <= 10; i++)                 //for index 8 to 10
    {
        p[i] = '8';                             //change p's index to '8'
    }
}