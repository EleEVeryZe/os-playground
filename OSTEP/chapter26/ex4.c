#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
/*
The Goal: Learn thread communication using Condition Variables.

Task: Create a shared "buffer" (a small array of size 5).

The Producer: A thread that generates random numbers and puts them in the buffer. If the buffer is full, it must wait.

The Consumer: A thread that takes numbers out of the buffer and prints them. If the buffer is empty, it must wait.

Challenge: Use pthread_cond_wait and pthread_cond_signal to make the threads talk to each other so they don't waste CPU cycles checking the buffer constantly.
*/

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
bool isFull = false;

typedef struct
{
    int *arr;
    int *arrIdx;
} SharedArr;

void fillArr(void *sharedArr)
{
    printf("\nStart fillArr");
    int i = 0;
    int *arr = ((SharedArr *)sharedArr)->arr;
    int *arrIdx = ((SharedArr *)sharedArr)->arrIdx;
    while (i < 30)
    {
        printf("\nvalueof arrIdx: %d\n", *arrIdx);
        pthread_mutex_lock(&lock);
        while (*arrIdx == 5)
        {
            pthread_cond_signal(&cond);
            pthread_cond_wait(&cond, &lock);
        }

        int rndm = rand() % 100;

        printf("\n[%d] - New Random Value: %d", i, rndm);
        *(arr + *arrIdx) = rndm;

        (*arrIdx)++;

        pthread_mutex_unlock(&lock);
        i++;
    }
}

void emptyArr(void *sharedArr)
{
    printf("\nStart emptyArr\n");
    int i = 0;
    int *arr = ((SharedArr *)sharedArr)->arr;
    int *arrIdx = ((SharedArr *)sharedArr)->arrIdx;

    while (i < 30)
    {
        printf("\nvalueof arrIdx: %d\n", *arrIdx);
        pthread_mutex_lock(&lock);
        while (*arrIdx == 0)
        {
            pthread_cond_signal(&cond);
            pthread_cond_wait(&cond, &lock);
        }
        printf("\n[%d] - Removed item: %d", i, *(arr + *arrIdx - 1));
        *(arr + *arrIdx) = -1;

        (*arrIdx)--;

        pthread_mutex_unlock(&lock);
        i++;
    }
}

int main()
{
    srand(time(NULL));
    printf("Start of program...\n");
    int *arr = malloc(sizeof(int) * 5);
    pthread_t prod, cons;
    int *arrIdx = malloc(sizeof(int));
    SharedArr sArr = {arr, arrIdx};

    if (pthread_create(&prod, NULL, fillArr, &sArr) != 0)
    {
        printf("NVidia, Fuck ou 1\n");
    }

    if (pthread_create(&cons, NULL, emptyArr, &sArr) != 0)
    {
        printf("NVidia, Fuck you 2\n");
    }

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    free(arr);
    free(arrIdx);
}