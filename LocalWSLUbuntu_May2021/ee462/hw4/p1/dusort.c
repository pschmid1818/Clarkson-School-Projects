#include "unistd.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

// goal:
// du --threshold=100 | sort -n

int main() {
    int fd[2];                                                      //variable declaration
    int pid;              

    char path[50];                                                  //change current directory to /usr/local
    strcpy(path, "/usr/local");
    if(chdir(path)==0) {
        printf("Directory changed to: %s\n", path);
    }
    else {
        printf("Could not change directory to %s\n", path);
        exit(EXIT_FAILURE);
    }
        

    if(pipe(fd) == 0) {                                             //create pipe
        pid = fork();
        if(pid == -1) {                                             //create fork, exit on fail
            printf("Fork could not be created\n");
            exit(EXIT_FAILURE);
        }
        if(pid == 0) {
            close(fd[0]);                                           //close read pipe, uneeded
            dup2(fd[1],1);                                          //copy the fd for the pipe into 1
            execlp("du","du", "--threshold=100", "-h", (char *)0);  //du for files larger than 100 (bytes is default) in a human readable foramt
            exit(EXIT_SUCCESS);
        }
        else {
            close(fd[1]);                                           //close write pipe, uneeded
            dup2(fd[0],0);                                          //copy the fd for the pipe into 0                     
            execlp("sort", "sort", "-n",  (char *)0);               //sort the input from du numerically
            exit(EXIT_SUCCESS);
        }
    }
    else {                                                          //exit on failed pipe creation
        printf("Pipe could not be created\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
