#include "unistd.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char *args[]) {
    if (argc != 2) {
        printf("Syntax Error: ./fltype p\\a\\th\nPath can be to a directory or file");
        exit(0);
    } 

    struct stat type;

    int s = stat(args[1], &type);

    if(S_ISREG(type.st_mode)) 
        printf("%s is a Regular File\n", args[1]);
    else if(S_ISDIR(type.st_mode))
        printf("%s is a Directory\n", args[1]);
    else if(S_ISBLK(type.st_mode))
        printf("%s is a Block Special File\n", args[1]);
    else if(S_ISCHR(type.st_mode))
        printf("%s is a Character Special File\n", args[1]);
    else if(S_ISFIFO(type.st_mode))
        printf("%s is a FIFO Special File\n", args[1]);   
    else if(S_ISLNK(type.st_mode))
        printf("%s is a Symbolic Link\n", args[1]);
    else if(S_ISSOCK(type.st_mode))
        printf("%s is a Socket\n", args[1]);
    else {
        printf("File type is unrecognized!\nRecognized types:\n");
        printf("Regular File\n");
        printf("Directory\n");
        printf("Block Special File\n");
        printf("Character Special File\n");
        printf("FIFO Special File\n"); 
        printf("Symbolic Link\n");
        printf("Socket\n");
    }
        
    return 0;
}
