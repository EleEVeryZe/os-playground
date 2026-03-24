#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
2. The Data Collector: Parallel Array Sum
The Goal: Learn how to pass data back from a thread.
    • Task: Create an array of 100 random integers. Create two threads: one to sum the first 50 elements and another to sum the last 50.
Challenge: Instead of using a global variable, have each thread return its partial sum to the main function using pthread_exit or by
passing a pointer. The main thread should then add the two results together and print the total.
*/

typedef struct {
    int start;
    int* arr;
} MyArr;

void *sum50(void *args)
{
    int start = ((MyArr *)args)->start;
    int *arr = ((MyArr *)args)->arr;
    int *sum = malloc(sizeof(int));
    *sum = 0;
    int i = 0;

    while (i < 50)
    {
        *sum += *(arr + start++) ;
        i++;
    }
    pthread_exit(sum);
}

int *generateRamdomArr()
{
    int *arr = malloc(sizeof(int) * 100);
    int i = 0;
    srand(time(NULL));

    while (i < 100)
    {
        int rndm = rand() % 100;
        printf("\n%d", rndm);
        *(arr + i++) = rndm;
    }
    return arr;
}

int main()
{
    int *arr = generateRamdomArr();
    MyArr data1 = {0, arr};
    MyArr data2 = {50, arr};
    
    pthread_t threadId1, threadId2;

    int result;
    if ((result = pthread_create(&threadId1, NULL, sum50, &data1)) != 0)
        return NULL;

    if ((result = pthread_create(&threadId2, NULL, sum50, &data2)) != 0)
        return NULL;

    void *rsp1, *rsp2;
    
    pthread_join(threadId1, &rsp1);
    pthread_join(threadId2, &rsp2);

    printf("\nThe Total was: %d\n", (*(int*)rsp1 + *(int*)rsp2));
    free(arr);
    free(rsp1);
    free(rsp2);
}