#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "unistd.h"
#include "string.h"

int main() {
    pid_t pid = fork();
    if(pid == -1) {
        printf("Error: Fork Failed!\n");
        exit(EXIT_FAILURE);
    }

    if(pid == 0) {
        printf("Child sleeping!\n");
        sleep(10);
        int ppid = getppid();

        char comm[20];
        int x = sprintf(comm,"ps aux | grep %d", ppid);
	printf("Parent Procces ID: %d", ppid);
        system(comm);
    }
    else {
        printf("Parent is leaving child!\n");
    }

    return EXIT_SUCCESS;
}
