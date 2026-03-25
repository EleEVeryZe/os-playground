#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
3. The Race Condition: The Shared Bank Account
The Goal: Understand why we need Mutexes.

Task: Create a global variable balance = 0. Create 10 threads, and have each thread run a loop 10,000 times that increments balance by 1.

The Experiment: Run the program without any synchronization. You’ll likely see that the final balance is less than 100,000.

The Fix: Use a pthread_mutex_t to lock the balance variable during the increment.

*/

long long int balance = 0;
int times = 5;
void *incrementBalance(void *args)
{
    long long int *balancer = (long long int*)args;
    long long int i = 0;
    long long int until = pow(10, times);
    while (i++ < until)
    {
        (*balancer)++;
    }
    printf("Thread[%ld] balance: %lld\n", pthread_self(), *balancer);
}

long long int balance2 = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void *incrementBalance2(void *args)
{
    long long int *balancer = (long long int)args;
    long long int i = 0;
    long long int until = pow(10, times);
    while (i++ < until)
    {
        pthread_mutex_lock(&lock);
        (*balancer)++;
        pthread_mutex_unlock(&lock);
    }
    printf("Thread[%ld] balance: %lld\n", pthread_self(), *balancer);
}

void initBalanceSum(void *incrementBalancer, long long int *balance)
{
    printf("Start of program...\n");
    pthread_t *tIds;
    if ((tIds = malloc(sizeof(pthread_t) * 10)) == NULL)
        return 1;

    int i = 0;
    while (i < 10)
    {
        if (pthread_create((tIds + i++), NULL, incrementBalancer, balance) != 0)
        {
            free(tIds);
            return NULL;
        }
    }
    i = 0;
    while (i < 10)
        pthread_join(*(tIds + i++), NULL);
    double raiz = pow(*balance, 1.0 / times);
    printf("Total sum of program: %f\n", (raiz));
    free(tIds);
}

int main() {
    printf("\nWithout locks:\n");
    initBalanceSum(incrementBalance, &balance);
    printf("\nNow using lock\n");
    initBalanceSum(incrementBalance2, &balance2);
}