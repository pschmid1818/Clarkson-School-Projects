#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    char *p = (char*) malloc(sizeof(char) * (12));    //allocate space for a char array
    p[0] = 'c';                                       //Set the values for 0 to 7
    p[1] = 'l';
    p[2] = 'a';
    p[3] = 'r';
    p[4] = 'k';
    p[5] = 's';
    p[6] = 'o';
    p[7] = 'n';

    pid_t child;                                    //saves the process id for the later wait
    int status = 0;                                 //boolean

    if (child = fork() == 0) //child process - no need for locks, pchild always executes first
    {
        for(int i = 8; i <= 10; i++)                //for index 8 to 10
        {
           p[i] = '3';                             //change p's index to '3'
        }
    
        printf("%s\n", p);                          //print p
    
        sleep(10);                                  //sleep for 10 seconds

        printf("%s\n", p);                          //print p
    }

    else //parent process - no need for locks, parent always executes second
    {
        sleep(3);                                   //sleep for 3 seconds
        for(int i = 8; i <= 10; i++)                 //for index 8 to 10
        {
            p[i] = '8';                             //change p's index to '8'
        }

        //printf("%s\n", p);                        //for testing
    }

    //sleep(7)                                      //while it works, I thought it didnt and moved to using a wait
    while ((child = wait(&status)) > 0);            //this waits for the child to finish - this solution was found on stackoverflow and modified for my own code https://stackoverflow.com/questions/19461744/how-to-make-parent-wait-for-all-child-processes-to-finish

    free(p);

    return 0;
}