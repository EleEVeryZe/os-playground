#include <stdlib.h>
#include <sys/wait.h>

#include <sys/stat.h>/* For mode constants */
#include <fcntl.h>   /* For O_RDWR, O_CREAT, etc. */
#include <unistd.h>  /* For open, read, write, close */
#include <stdio.h>   /* For standard I/O functions */


int main() {
    int rc = fork();

    if (rc == 0) {
        printf("Hello");
    }

    if (rc > 0)
    {
        wait(NULL);
        printf("Good bye");
    }
    return 0;
}