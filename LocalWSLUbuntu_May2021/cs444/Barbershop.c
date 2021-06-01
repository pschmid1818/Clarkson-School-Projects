#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"
#include "semaphore.h"

int n;
int customers;
int closing;

sem_t mutex;
sem_t customerSem;
sem_t barberSem;
sem_t customerDone;
sem_t barberDone;

pthread_t barber;
pthread_t *customer;

void shutdown() {
    pthread_exit(&barber);
    for(int i = 0; i > 7; i++) {
        pthread_exit(&customer[i]);
    }

    sem_destroy(&mutex);
    sem_destroy(&customerSem);
    sem_destroy(&barberSem);
    sem_destroy(&customerDone);
    sem_destroy(&barberDone);
}

void cutHair() {
    printf("Barber is cutting hair\n");
}

void getHairCut(pthread_t name) {
    printf("Thread %ld is getting it's hair cut\n", name);
}

void balk(pthread_t name) {
    printf("Screw you guys, Thread %ld is goin' home!\n", name);
    sem_post(&mutex);
    pthread_exit(&name);
}

void * barberRunner(void * args) {
    while(!closing) {
            
        sem_wait(&customerSem);
        sem_post(&barberSem);

        cutHair();

        sem_wait(&customerDone);
        sem_post(&barberDone);
    }

    printf("Barber is leaving\n");
    pthread_t self = pthread_self();
    pthread_exit(&self);
}

void * customerRunner(void * args) {
    pthread_t self = pthread_self();

    sem_wait(&mutex);
    if(customers >= n) 
        balk(self);
    customers++;
    sem_post(&mutex);

    sem_post(&customerSem);
    sem_wait(&barberSem);

    getHairCut(self);

    sem_post(&customerDone);
    sem_wait(&barberDone);

    sem_wait(&mutex);
    customers--;
    sem_post(&mutex);

    pthread_exit(&self);
}

int main(int argc, char *args[]) {

    if(argc != 2) {
        printf("./BarbershopC n\nWhere n = number of seats\n");
        exit(0);
    }
    char *input = args[1];
    n = atoi(input);
    customers = 0;
    closing = 0;

    sem_init(&mutex, 0, 1);
    sem_init(&customerSem, 0, 1);
    sem_init(&barberSem, 0, 1);
    sem_init(&customerDone, 0, 1);
    sem_init(&barberDone, 0, 1);

    barber;
    customer = malloc(7 * sizeof(pthread_t));
    
    if(pthread_create(&barber, NULL, barberRunner, NULL) != 0) {
        printf("Error creating barber thread\n");
        shutdown();
        exit(0);
    }

    sem_post(&mutex);

    int timesRun = 5;
    for (int i = 0; i < timesRun; i++) {
        sleep(3);


        time_t t;
        srand((unsigned) time(&t));
        int x = (rand() % 5) + 1;

        printf("%d new threads have arrived!\n", x);

        if(i == timesRun - 1) {
           closing = 1;
        }

        for(int i = 0; i < x; i++) {
            if(pthread_create(&customer[i], NULL, customerRunner, NULL) != 0) {
                printf("Error creating customer thread\n");
                shutdown();
                exit(0);
            } 
        }
    }

    pthread_join(barber, NULL);
    shutdown();
    free(customer);
    return 0;
}