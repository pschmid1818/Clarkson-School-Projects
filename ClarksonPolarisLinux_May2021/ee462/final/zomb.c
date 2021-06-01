#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "unistd.h"

void findZombie() {
    printf("Finding all zombie processes...\n");
    system("ps aux | grep 'Z'");                
}

int main() {
    pid_t pid = fork();
    if(pid == -1) {
        printf("Error: Fork Failed!\n");
        exit(EXIT_FAILURE);
    }

    if(pid == 0) {
        printf("Killing child...\n");
        exit(EXIT_SUCCESS); //child exits
    }
    else {
        printf("Parent Waiting...\n");
        sleep(10);          //parent sleeps
    }

    findZombie();

    return EXIT_SUCCESS;
}
