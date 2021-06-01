#include "unistd.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "dirent.h"

void isType(int fltype, char *path, char *item);
int handleFlags(int argc, char **args);

int main(int argc, char *args[]) {
    if (argc < 2) {
        printf("Syntax Error: ./lf path flags\nFlags can be:\n-d (directory)\n-r (regular file)\n-s (symbolic link)");
        exit(0);
    } 

    int fltype = handleFlags(argc, args);
    DIR *target;
    struct dirent *item;

    target = opendir(args[1]);

    if(target) {
        while ((item = readdir(target)) != NULL) {
            char *path = malloc(100 * sizeof(char));
            strcat(path, args[1]);
            strcat(path, item->d_name);
            isType(fltype, path, item->d_name);
            free(path);
        }
        closedir(target);
    }

    
    return 0;
}

void isType(int fltype, char *path, char *item) {
    struct stat type;
    int s = stat(path, &type);
    if(item[0] == '.')
        return;


    if(fltype == 1) {
        if(S_ISDIR(type.st_mode))
            printf("Directory: %s\n", item);
    }
    if(fltype == 2) {
        if(S_ISREG(type.st_mode))
            printf("Regular File: %s\n", item);
    }
    if(fltype == 3) {
        if(S_ISLNK(type.st_mode))
            printf("Symbolic Link: %s\n", item);
    }
    if(fltype == 4) {
        if(S_ISDIR(type.st_mode))
            printf("Directory: %s\n", item);
        else if(S_ISREG(type.st_mode))
            printf("Regular File: %s\n", item);
    }
    if(fltype == 5) {
        if(S_ISDIR(type.st_mode))
            printf("Directory: %s\n", item);
        else if(S_ISLNK(type.st_mode))
            printf("Symbolic Link: %s\n", item);
    }
    if(fltype == 6) {
        if(S_ISREG(type.st_mode))
            printf("Regular File: %s\n", item);
        else if(S_ISLNK(type.st_mode))
            printf("Symbolic Link: %s\n", item);
    }
    if(fltype == 7) {
        if(S_ISDIR(type.st_mode))
            printf("Directory: %s\n", item);
        else if(S_ISREG(type.st_mode))
            printf("Regular File: %s\n", item);
        else if(S_ISLNK(type.st_mode))
            printf("Symbolic Link: %s\n", item);
    }
}

int handleFlags(int argc, char **args) {

    int count = 0;
    char **fltypes = malloc(3 * 5 * sizeof(char));

    /*
    In this for loop, the command line is checked to find which flags were called
    this for loop will add the calls as words in the fltypes string array
    it accounts for all possible flag combinations between -d -r and -s given -drs works
    */
    for(int i = 2; i < argc; i++) {
        if (!strcmp(args[i], "-d")) {
             fltypes[count] = "dir";
        }
        if (!strcmp(args[i], "-r")) {
            fltypes[count] = "reg";
        }
        if (!strcmp(args[i], "-s")) {
            fltypes[count] = "sym";
        }
        if (!strcmp(args[i], "-dr")) {
            fltypes[count] = "dir";
            fltypes[count + 1] = "reg";
            count++;
        }
        if (!strcmp(args[i], "-ds")) {
            fltypes[count] = "dir";
            fltypes[count + 1] = "sym";
            count++;
        }
        if (!strcmp(args[i], "-rd")) {
            fltypes[count] = "dir";
            fltypes[count + 1] = "reg";
            count++;
        }
        if (!strcmp(args[i], "-sd")) {
            fltypes[count] = "dir";
            fltypes[count + 1] = "sym";
            count++;
        }
        if (!strcmp(args[i], "-rs")) {
            fltypes[count] = "sym";
            fltypes[count + 1] = "reg";
            count++;
        }
        if (!strcmp(args[i], "-sr")) {
            fltypes[count] = "sym";
            fltypes[count + 1] = "reg";
            count++;
        }
        if (!strcmp(args[i], "-drs")) {
            fltypes[count] = "dir";
            fltypes[count + 1] = "reg";
            fltypes[count + 2] = "sym";
            count = count + 2;
        }
        if (!strcmp(args[i], "-rds")) {
            fltypes[count] = "dir";
            fltypes[count + 1] = "reg";
            fltypes[count + 2] = "sym";
            count = count + 2;
        }
        if (!strcmp(args[i], "-sdr")) {
            fltypes[count] = "dir";
            fltypes[count + 1] = "reg";
            fltypes[count + 2] = "sym";
            count = count + 2;
        }
        if (!strcmp(args[i], "-rsd")) {
            fltypes[count] = "dir";
            fltypes[count + 1] = "reg";
            fltypes[count + 2] = "sym";
            count = count + 2;
        }
        if (!strcmp(args[i], "-srd")) {
            fltypes[count] = "dir";
            fltypes[count + 1] = "reg";
            fltypes[count + 2] = "sym";
            count = count + 2;
        }
        if (!strcmp(args[i], "-dsr")) {
            fltypes[count] = "dir";
            fltypes[count + 1] = "reg";
            fltypes[count + 2] = "sym";
            count = count + 2;
        }
        count++;
    }

    /*
    This block gives an output as an int using the string array's possible values
    0 = none 
    1 = dir
    2 = reg
    3 = sym
    4 = dir + reg
    5 = dir + sym
    6 = reg + sym
    7 = dir + reg + sym
    */
    
    int fltype = 0;
    if(count == 1) {
        if(!strcmp(fltypes[0], "dir")) 
            fltype = 1;
        if(!strcmp(fltypes[0], "reg")) 
            fltype = 2;
        if(!strcmp(fltypes[0], "sym")) 
            fltype = 3;
    }
    else if(count == 2) {
        if((!strcmp(fltypes[0], "dir") && !strcmp(fltypes[1], "reg")) || (!strcmp(fltypes[0], "reg") && !strcmp(fltypes[1], "dir"))) 
            fltype = 4;
        if((!strcmp(fltypes[0], "dir") && !strcmp(fltypes[1], "sym")) || (!strcmp(fltypes[0], "sym") && !strcmp(fltypes[1], "dir"))) 
            fltype = 5;
        if((!strcmp(fltypes[0], "sym") && !strcmp(fltypes[1], "reg")) || (!strcmp(fltypes[0], "reg") && !strcmp(fltypes[1], "sym"))) 
            fltype = 6;
    }
    else {
        if((!strcmp(fltypes[0], "dir") && !strcmp(fltypes[1], "reg") && !strcmp(fltypes[2], "sym")) || (!strcmp(fltypes[0], "dir") && !strcmp(fltypes[1], "sym") && !strcmp(fltypes[2], "reg")) || (!strcmp(fltypes[0], "reg") && !strcmp(fltypes[1], "dir") && !strcmp(fltypes[2], "sym")) || (!strcmp(fltypes[0], "reg") && !strcmp(fltypes[1], "sym") && !strcmp(fltypes[2], "sir")) || (!strcmp(fltypes[0], "sym") && !strcmp(fltypes[1], "reg") && !strcmp(fltypes[2], "dir")) || (!strcmp(fltypes[0], "sym") && !strcmp(fltypes[1], "dir") && !strcmp(fltypes[2], "reg")))
            fltype = 7;
    }

    free(fltypes);
    return fltype;
}
