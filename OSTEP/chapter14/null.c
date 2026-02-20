#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
/*
1. First, write a simple program called null.c that creates a pointer
to an integer, sets it to NULL, and then tries to dereference it. Compile this into an executable called null. What happens when you
run this program?
*/

/*
2. Next, compile this program with symbol information included (with
the -g flag). Doing so let’s put more information into the executable, enabling the debugger to access more useful information
about variable names and the like. Run the program under the
debugger by typing gdb ./null and then, once gdb is running,
typing run. What does gdb show you?

*/

/*
Finally, use the valgrind tool on this program. We’ll use memcheck
that is a part of valgrind to analyze what happens. Run this by
typing in the following: valgrind --leak-check=yes ./null.
What happens when you run this? Can you interpret the output
from the tool?

*/

int ex1_2()
{
    int *p = NULL;
    int value = *p;
    printf("END");
    return 0;
}

int ex1_3() {
    int *mal = malloc(sizeof(int));

    return 0;
}

int main()
{
    ex1_3();
}

/*
Explanation

The Protection: Most Operating Systems intentionally leave address 0 unmapped.
This means there is no "Physical Address" associated with it, and its "Protection Bits" are set to "No Access."
*/


int curiosity()
{
    int n;
    printf("My PID is: %d\n", getpid());
    printf("Go to another terminal and run: cat /proc/%d/maps\n", getpid());
    printf("Waiting for input to stay alive...\n");
    printf("Thanks for the time...\n");

    scanf("%d", &n); // Program stops here, keeping the memory map active

    /*
    Part 1: Your Program (null)
        These first 5 lines are the "Binary Image" of your specific program.

        590516c58000-590516c59000 r--p: Read-only Data. This stores constants and global variables that don't change.

        590516c59000-590516c5a000 r-xp: The Code (Text) Segment. This contains your actual machine instructions. Notice the x (executable).

        590516c5a000-590516c5b000 r--p: More read-only metadata about your executable.

        590516c5b000-590516c5c000 r--p: Relocation tables used to fix addresses at startup.

        590516c5c000-590516c5d000 rw-p: Global/Static Data. This is where global variables you can change are stored. Notice the w (writeable).

        Part 2: The Heap
        590554d6e000-590554d8f000 rw-p ... [heap]: This is the sandbox for your malloc() calls. It’s marked rw because you need to read and write data here. It grows "upward" as you allocate more.

        Part 3: The Standard C Library (libc)
        Your program doesn't know how to talk to the screen or the keyboard; it asks libc to do it.

        704af2c00000... r--p: libc constants.

        704af2c28000... r-xp: The printf/scanf logic. This is the executable code of the C library.

        704af2db0000... r--p: Read-only data used by libc.

        704af2e03000... rw-p: Internal libc state. Global variables that the C library uses to track things (like stdout buffering).

        Part 4: The Dynamic Linker (ld-linux)
        This is the "glue" that attached libc to your program when you ran it.

        704af2e64000... r-xp: The executable code of the linker itself.

        Part 5: The "Top" of the World
        7fffecb51000... rw-p ... [stack]: This is where your local variables live. It grows "downward" toward the heap.

        [vvar] & [vdso]: These are "cheat codes." The OS maps a tiny bit of its own memory into your process so you can check the system time or get the PID without performing a slow System Call.
    */

    return 0;
}