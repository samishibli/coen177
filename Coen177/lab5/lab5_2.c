// Name: Sami Shibli
// Date: Tue May 7th
// Title: Lab5 – Step 1 - Using Mutex Locks
// Description: This program demonstrates the use of mutex locks to synchronize threads
//              accessing a shared buffer. It implements a scenario where multiple threads
//              concurrently modify a shared resource, ensuring that only one thread accesses
//              the resource at a time using mutex locks.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define NTHREADS 10

void *go(void *arg);
void cleanup(int sigtype);

pthread_t threads[NTHREADS];
pthread_mutex_t mutex;

int main()
{
    signal(SIGINT, cleanup);
    pthread_mutex_init(&mutex, NULL); // Initialize the mutex
    int i;
    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    for (i = 0; i < NTHREADS; i++)
        pthread_join(threads[i], NULL);
    pthread_mutex_destroy(&mutex); // Destroy the mutex
    return 0;
}

void *go(void *arg)
{
    printf("Thread %d is now attempting ....\n", (int)(size_t)arg);
    pthread_mutex_lock(&mutex); // Lock the mutex
    sleep(1);
    printf("Thread %d is running in its Critical Section........\n", (int)(size_t)arg);
    pthread_mutex_unlock(&mutex); // Unlock the mutex
    pthread_exit(0);
}

void cleanup(int sigtype)
{
    pthread_mutex_destroy(&mutex);
    printf("\n Terminating\n");
    exit(0);
}
