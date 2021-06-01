#include "unistd.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "signal.h"

FILE *f; 
static void grclose(int sig, siginfo_t *siginfo, void *context);

int main(int argc, char *args[]) {
    if (argc != 2) {
        printf("Syntax incorrect:\nsimtee output.file\nexiting...\n");
        exit(0);
    }

    struct sigaction act;               
    memset(&act, '\0', sizeof(act));    
    act.sa_sigaction = &grclose;        
    act.sa_flags = SA_SIGINFO;          

    f = fopen(args[1], "w");
    char *input = malloc(100 * sizeof(char));

    printf("To be written to file %s, enter to end, ^C to exit gracefully:\n", args[1]);

    do {
        strcpy(input,"\n");
        fgets(input, 100, stdin);
        fwrite(input, sizeof(char), strlen(input), f);
        printf("%s", input);
       
        if (sigaction(SIGINT, &act, NULL)) { 
            printf("sigaction error\nexiting...\n");
            exit(0);
        }                           
    
    } while(strcmp(input,"\n"));
    

    fclose(f);
    printf("File %s has been closed\n", args[1]);

    return 0;
}

static void grclose(int sig, siginfo_t *siginfo, void *context) {
    printf("%s", "\n");
    fwrite("closing file gracefuly\n", sizeof(char), strlen("closing file gracefuly\n"), f);
    fclose(f);
    exit(0);
}