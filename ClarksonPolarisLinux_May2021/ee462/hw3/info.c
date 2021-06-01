#include "unistd.h"
#include "stdio.h"
#include "sys/types.h"
#include "stdlib.h"
#include "string.h"

int main() {
    //declare variables needed throughout the code
    char *name = malloc(100 * sizeof(char));
    char *cwd = malloc(100 * sizeof(char));
    char *fullpath = malloc(100 * sizeof(char));
    pid_t pid;
    pid_t ppid;
    char *prd = malloc(100 * sizeof(char));
    char *pexec = malloc(100 * sizeof(char));

    if (fork() == 0) {
        chdir("/tmp");
        char cwd[100];
        name = "Child";
    }
    else {
        name = "Original";
    }
    
    pid = getpid();                                             //get current process id
    ppid = getppid();                                           //get parent process id
    getcwd(cwd, sizeof(cwd));                                   //get current working directory

    int count = readlink("/proc/self/cwd", prd, 100);           //find the link to process root directory
    prd[count] = 0;                                             //set prd to process root directory

    count = readlink("/proc/self/exe", pexec, 100);             //find the link to full name of the executable of the process
    pexec[count] = 0;                                           //set pexec to full name of the executable of the process

    printf("%s: Current PID: %d\n", name, pid);                 //print process id
    printf("%s: Parent PID: %d\n", name, ppid);                 //print parent process id
    printf("%s: Current Working Directory: %s\n", name, cwd);   //print current working directory
    printf("%s: Process Root Directory: %s\n", name, prd);      //print process root directory
    printf("%s: Process Executable: %s\n", name, pexec);        //print full name of the executable of the process

    return 0;
}
