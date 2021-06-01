#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"


int main(int argc, char *args[]) {
    int f;

    if (argc == 2) {
        f = open("nf1.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        printf("With O_RDWR\n");
    }
    else
        f = open("nf1.txt", O_RDONLY | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    
    if(f == -1) {
        perror("Can't Open file...\n");
        exit(0);
    }
    int fd = dup(f);

    printf("File FD: %d\nDup FD: %d\n", f, fd);
    if(f == fd) 
        printf("File Descriptors match!\n");
    else
        printf("File Descriptors do not match...\n");

    printf("\n");

    int fmodes = fcntl(f, F_GETFL);
    int fdmodes = fcntl(fd, F_GETFL);

    printf("File Status Flags: %d\nDup Status Flags: %d\n", fmodes, fdmodes);
    if(fmodes == fdmodes) 
        printf("Status Flags match!\n");
    else
        printf("Status Flags do not match...\n");

    printf("\n");

    
    off_t foff = lseek(f, 0, SEEK_CUR);
    off_t fdoff = lseek(fd, 0, SEEK_CUR);
    printf("File Offset: %ld\nDup Offset: %ld\n", foff, fdoff);

    printf("\n");

    close(fd);
    close(f);
}