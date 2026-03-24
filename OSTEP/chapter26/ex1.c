#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
/**
The Goal: Learn how to create and join threads.
    • Task: Write a program that creates 5 threads.
    Each thread should print: "Hello from thread [ID]!",
    where [ID] is the unique number passed to the thread from the main function.

    Challenge: Ensure the main program waits for all 5 threads to finish before printing "All threads have finished. Exiting."
 */

void *printer(void *args)
{
    int id = pthread_self();
    printf("Hello world from [%d]\n", id);
    return NULL;
}
int main()
{
    printf("Starting program...\n");
    int i = 0;
    pthread_t *thread_ids;
    if ((thread_ids = malloc(sizeof(pthread_t) * 5)) == 0)
        return NULL;
    
    while (i < 5)
    {
        pthread_t thread_id;
        int result;
        if ((result = pthread_create(&thread_id, NULL, printer, "12334")) != 0){
            printf("Failed to create new Thread");
            return NULL;
        }
        thread_ids[i] = thread_id;
        i++;
    }

    i = 0;

    while (i < 5)
        pthread_join(thread_ids[i++], NULL);

    free(thread_ids);
    printf("All threads have finished. Exiting");
    return 0;
}