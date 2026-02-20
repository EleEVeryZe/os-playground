#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int x = 100; // Set value before fork
    printf("Before fork: x is %d\n", x);

    int rc = fork();

    if (rc < 0) {
        // Fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // Child process
        printf("Child process: initial x is %d\n", x);
        x = 200;
        printf("Child process: after change, x is %d\n", x);
    } else {
        // Parent process
        // wait(NULL); // Uncomment this to make parent wait for child
        printf("Parent process: initial x is %d\n", x);
        x = 300;
        printf("Parent process: after change, x is %d\n", x);
    }

    return 0;
}