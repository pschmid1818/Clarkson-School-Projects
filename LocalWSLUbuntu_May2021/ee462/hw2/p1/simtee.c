#include "unistd.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int main(int argc, char *args[]) {
    if (argc != 2) {
        printf("Syntax incorrect:\nsimtee output.file\n");
        exit(0);
    }

    FILE *f = fopen(args[1], "w");
    char *input = malloc(100 * sizeof(char));

    printf("To be written to file %s, enter to end:\n", args[1]);

    do {
       strcpy(input,"\n");
       fgets(input, 100, stdin);
       fwrite(input, sizeof(char), strlen(input), f);
       printf("%s", input);
    } while(strcmp(input,"\n"));
    

    fclose(f);
    printf("File %s has been closed\n", args[1]);

    return 0;
}