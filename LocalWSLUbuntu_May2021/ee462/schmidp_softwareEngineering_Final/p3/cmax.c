#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "unistd.h"
#include "string.h"
#include "pthread.h"

pthread_t *threads;                             //create an array of threads

void shutdown() {                               //exit all threads before shutdown
    for(int i = 1; i > 4; i++) {
        pthread_exit(&threads[i]);
    }
}

int findIndex(pthread_t *threads, pthread_t indVal, size_t size) {
    int index = -1;                  //gives a return for if nothing is found

    for(int i = 0; i < size; i++) {
        if(threads[i] == indVal) {
            index = i;              //if current thread index matches indValue, thats the index
            break;                  //break when found
        }
    }

    return index;
}

void * threadRunner(void * args) {

    pthread_t id = pthread_self();                          //find thread id
    int index = findIndex(threads, id, sizeof(threads));    //find index of thread for file name
    if(index == -1) {
        printf("Error finding index for thread %ld\n", id);
        shutdown();
        exit(EXIT_FAILURE);
    }

    char fileName[20];
    int n = sprintf(fileName, "data4/inp_%d.txt", index);   //get file name
    FILE *file= fopen(fileName, "r");                       //open file
    if(file == NULL) {             
        printf("Error opening file %s\n", fileName);
        shutdown();
        exit(EXIT_FAILURE);
    } 

    int scan[100];
    int num, max;
    fscanf(file, "%d", scan);                              //read file
    max = 0;

    while(!feof(file)) {                                   //read every line for whole file
        fscanf(file, "%d", &num);                          
        if(num > max) {                                    
            max = num;                                     //if line is > max, this line is new max
        }
    }

    printf("Max for %s is: %d\n", fileName, max);

    fclose(file);

    n = sprintf(fileName, "data4/out_%d.txt", index);       //get new file name
    FILE *output= fopen(fileName, "w");                     //open new file

    char maxStr[20];
    n = sprintf(maxStr, "%d", max);
    fwrite(maxStr, sizeof(char), sizeof(maxStr), output);
    fwrite("\n", sizeof(char), sizeof("\n"), output);
    
    fclose(output);
}

int main() {  
    threads = malloc(6 * sizeof(pthread_t));                            //allocate memory to the array 

    for(int i = 1; i < 4; i++) {
        printf("Creating thread %d\n", i);
        if(pthread_create(&threads[i], NULL, threadRunner, NULL) != 0) {//create thread
            printf("Error creating thread %d\n", i);
            shutdown();
            exit(0);
        }
    }

    //wait for threads to end
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);

    shutdown();
    free(threads);                                                     //free memory used by threads
    return EXIT_SUCCESS;
}