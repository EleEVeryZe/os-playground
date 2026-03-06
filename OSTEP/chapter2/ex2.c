#include <stdlib.h>
#include <sys/wait.h>

#include <sys/stat.h>/* For mode constants */
#include <fcntl.h>   /* For O_RDWR, O_CREAT, etc. */
#include <unistd.h>  /* For open, read, write, close */
#include <stdio.h>   /* For standard I/O functions */


int main() {
    char buffer[10];

    int fd = open("hello-c", O_RDWR | O_CREAT);

    int rc = fork();

    if (rc == 0) {
        write(fd, "Hello word from child, mother fucker", 22);
        printf("Child process %d", fd);
    }

    if (rc > 0){
        write(fd, "Hello word from father, mother fucker", 22);
        printf("Fathers process %d", fd);
    }

    lseek(fd, 0, SEEK_SET); //this return fd to the position 0, making parent and child process printf the same thing. 


    read(fd, buffer, sizeof(buffer) - 1);
    printf("Read from file: %s\n", buffer);

    return 0;
        
}