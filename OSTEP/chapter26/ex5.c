#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
/*
The Goal: Master different types of access levels.
	• The Scenario: Imagine a shared database. Multiple threads want to read from it at the same time (which is safe), 
        but only one thread can write to it at a time (which is exclusive).
	• Task: Create 5 "Reader" threads and 2 "Writer" threads.
	• The Rule: Readers can enter the "database" simultaneously unless a Writer is currently writing. If a Writer is writing, no one else can be in the database.
Challenge: Use mutexes and counters to track how many readers are active so the last reader out can signal that the database is free for a writer.
*/
int BUFFER_SIZE = sizeof(char) * 10;

typedef struct{
    char *file;
} ReadResource;

typedef struct{
    char *prevString;
    char *newString;
} WriteResource;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int isWriting = 0;
int readCount = 0;

void *read(void *args) {
    pthread_mutex_lock(&lock);
    while (isWriting == 1)
        pthread_cond_wait(&cond, &lock);
    

    readCount++;
    pthread_mutex_unlock(&lock);

    char *rsrc = ((ReadResource *)args)->file;
    char *newStrg = malloc(BUFFER_SIZE);
    if (strcp(rsrc, newStrg, BUFFER_SIZE) != 0)
        return;
    printf("\nREAD: %s", newStrg);

    pthread_mutex_lock(&lock);

    readCount--;
    pthread_cond_broadcast(&cond);

    pthread_mutex_unlock(&lock);
}

void *write(void *args){
    pthread_mutex_lock(&lock);
    while (isWriting || readCount > 0)
        pthread_cond_wait(&cond, &lock);
        
    isWriting = 1;
    pthread_mutex_unlock(&lock);

    char *prevString = ((WriteResource *) args)->prevString;
    char *newString = ((WriteResource *) args)->newString;

    if (strcp(prevString, newString, BUFFER_SIZE) != 0)
        return;
    printf("\nWRITTEN: %s", newString);

    pthread_mutex_lock(&lock);
    isWriting = 0;
    pthread_mutex_unlock(&lock);
    pthread_cond_broadcast(&cond);
}

int main() {
    pthread_t *threadRW;
    if ((threadRW = malloc(sizeof(pthread_t) * 7)) == 0){
        printf("Malloc New Thread Failed");
        return;
    }

    int i = 0;
    while (i < 5)
        if (pthread_create((threadRW + i), NULL, read, NULL) != 0)
        {
            printf("Create New Thread Failed");
            return;
        }
    i = 0;
    while (i++ < 2)
        if (pthread_create((threadRW + i), NULL, write, NULL) != 0)
        {
            printf("Create New Thread Failed");
            return;
        }   

    while (i++ < 7)
        pthread_join((threadRW + i));

    free(threadRW);
}