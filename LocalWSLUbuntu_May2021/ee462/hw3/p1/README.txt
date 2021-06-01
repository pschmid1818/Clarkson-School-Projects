compiled with: gcc grtee.c -o grtee
*note: compiled and run in WSL Ubuntu, may need -std=c99 flag added

Added: 
#include "signal.h"     - used to call sigaction and related functions and globals

struct sigaction act;               - sigaction called act
memset(&act, '\0', sizeof(act));    - set the memory of act
act.sa_sigaction = &grclose;        - set act to run grclose
act.sa_flags = SA_SIGINFO;          - tell sigaction to use sa_sigaction field

if (sigaction(SIGINT, &act, NULL)) {            - signal grclose to close the code when ctrl + C (^C aka. SIGINT) is entered
    printf("sigaction error\nexiting...\n");    - displays error message
    exit(0);                                    - exits program with status 0
}

static void grclose(int sig, siginfo_t *siginfo, void *context) {                               - takes in a signal for SIGINT
    printf("%s", "\n");                                                                         - prints a newline to terminal
    fwrite("closing file gracefuly\n", sizeof(char), strlen("closing file gracefuly\n"), f);    - writes closing file gracefully to f
    fclose(f);                                                                                  - closes file f
    exit(0);                                                                                    - exits program with status 0
}

Changed:
File *f;    - moved to become global variable for grclose to use

--- Output --------------------------------------------------------

$ gcc grtee.c -o grtee
$ ./grtee out.txt
To be written to file out.txt, enter to end, ^C to exit gracefully:
this is a test of simtee
this is a test of simtee
this should be written
this should be written
so should this
so should this


File out.txt has been closed
$ cat out.txt
this is a test of simtee
this should be written
so should this

$ ./grtee out.txt
To be written to file out.txt, enter to end, ^C to exit gracefully:
this is a test of grtee
this is a test of grtee
this should be written
this should be written
this should not^C
$ cat out.txt
this is a test of grtee
this should be written
closing file gracefuly
$