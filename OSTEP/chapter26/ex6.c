#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    The web crawler: string processing
    The Goal: Handling strings and dynamic memory across threads.
    • Task: Create a "Work Queue" of 10 different strings (URLs). Create 3 worker threads.
    • The Process: Each thread grabs a URL from the queue, "processes" it (e.g., counts the vowels or reverses the string, or sum the ocurrence of a), and prints the result along with its Thread ID.
    Challenge: Ensure that no two threads grab the same URL. You’ll need a mutex to protect the index variable that tracks which URL is next.
    */
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct
{
    char *urls[10];
    int idx;
} URLs;

URLs urls = {
    .urls = {
        "https://www.google.com/",
        "https://wikipedia.org",
        "https://github.com",
        "https://stackoverflow.com",
        "https://reddit.com",
        "https://youtube.com",
        "https://linkedin.com",
        "https://microsoft.com",
        "https://apple.com",
        "https://amazon.com"},
    .idx = 0};

void *workerThread()
{

    pthread_mutex_lock(&lock);

    if (urls.idx >= 10)
    {
        pthread_mutex_unlock(&lock);
        return;
    }

    int currentIdx = urls.idx++;
    pthread_mutex_unlock(&lock);

    char letter = '';
    int j = 0;
    int numOfA = 0;
    while (letter != '\0')
        if ((letter = urls.urls[currentIdx][j++]) == 'a')
            numOfA++;
    printf("[%d] - OCORRENCES OF A IN STRING [%s] IS %d", pthread_self(), urls.urls[currentIdx], numOfA);
}

int main()
{
    pthread_t *threads = malloc(sizeof(pthread_t) * 3);

    for (int i = 0; i < 3; i++)
        pthread_create(threads[i], NULL, workerThread, NULL);

    for (int i = 0; i < 3; i++)
        pthread_join(threads[i], NULL);

    free(threads);
}