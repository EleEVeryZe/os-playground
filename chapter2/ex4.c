#include <stdlib.h>
#include <sys/wait.h>

#include <sys/stat.h>/* For mode constants */
#include <fcntl.h>   /* For O_RDWR, O_CREAT, etc. */
#include <unistd.h>  /* For open, read, write, close */
#include <stdio.h>   /* For standard I/O functions */

/**
Why are there so many exec?

In reality, there is only one core system call on Linux/Unix that the kernel actually 
executes: execve. All the other variations (like execlp, execv, etc.) are "wrapper" 
functions in the standard C library (libc). They exist to make the programmer's 
life easier by handling different ways of providing data to that one core system call.
 */

int main5() {
    int rc = fork();

    if (rc == 0){
        execlp("ls", "ls", "-l", (char *)NULL); //Arguments are passed as a comma-separated list.
        return 1;
    }

    return 0;
}


/** 
 Parent Finishes Early: While your child is off running ls, your parent process immediately hits return 0;
 and exits. In many terminal environments, if the parent exits before the child finishes its output, 
 the shell prompt might return while the child's output is still printing, or the terminal may wait for the entire 
 process group, leading to the "hang" you see. 
 */
    int main6() {
        int rc = fork();

        if (rc == 0) {
            printf("Son says hi ");
            char *args[] = { //this is a pointer to pointers (a verctor). These pointers point to string
                "/bin/ls",
                "-l",
                "-a",
                NULL
            };
            execv("/bin/ls", args);
            
            printf("Son of the son says hi");
            return 1;
        }
        if (rc > 0){
            wait(&rc);
            printf("Dad says hi");
        }
        return 0;
    }

/**
With waitpid(pid, &status, 0), you specify the exact pid you want to wait for. This allows your parent process
to synchronize with a specific task while ignoring others that may still be running.

Recommendation: For portable and professional applications, always use waitpid. Even when waiting for 
"any" child, waitpid(-1, &status, 0) is functionally equivalent to wait(&status) but leaves your code 
ready for more advanced options later.
 */

    int main7() {
        int rc = fork();

        if (rc == 0) {
            printf("I'm a child process");
        } else {
            waitpid(rc, NULL, 0);
            printf("I'm a parent process");
        }
    }

    int main8() {
        int rc = fork();

        if (rc == 0){
            printf("Im a child");
        }
            
        else {
            waitpid(rc, NULL, 0);
            printf("Im a parent");
            close(STDOUT_FILENO); //Equivalent: close(1);
        }
    }

    int main9() {
        int rc1 = fork();

        if (rc1 == 0) {
            printf("_ rc1 %d", rc1);
            exit(0);
        }

        
        int rc2 = fork();
        if (rc2 == 0) {
            printf("_ rc2 %d", rc2);
            exit(0);
        }

        if (rc1 > 0 || rc2 > 0) {
            waitpid(-1, NULL, 0);
            printf(" (Parent 1:%d 2: %d) ", rc1, rc2);
            
        }
    }

    int main10() {
        int fd[2];

        if (pipe(fd) == -1){
            perror("Pipe failed");
            return 1;
        }

        int rc1 = fork();
        if (rc1 == 0) {
            dup2(fd[1], STDOUT_FILENO);

            //Its redundant because dup2 has already created a copy of them.
            close(fd[0]);
            close(fd[1]);

            printf("Thiss is rc1 - ");
            exit(0);
        }

        int rc2 = fork();
        if (rc2 == 0) {
            dup2(fd[1], STDOUT_FILENO);

            //Its redundant because dup2 has already created a copy of them.
            close(fd[0]);
            close(fd[1]);

            printf("Thiss is rc2 - ");
            exit(0);
        }

        close(fd[1]);

        char buffer[5];
        int bytesRead;

        while ((bytesRead = read(fd[0], buffer, sizeof(buffer))) > 0) {
            buffer[bytesRead] = '\0'; // Null-terminate the string
            printf("Parent received from pipe: %s\n", buffer);
        }

        close(fd[0]); // Done reading


        waitpid(rc1, NULL, 0);
        waitpid(rc2, NULL, 0);
        return 0;

    }

    int main() {
        main10();
    }