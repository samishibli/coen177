#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);

#define NTHREADS 10
pthread_t threads[NTHREADS];

// an array to hold the values for each thread
int args[NTHREADS];

int main()
{
    int i;
    for (i = 0; i < NTHREADS; i++)
    {
        // assing the value of i to the args array rather than sharing the same address for all threads
        args[i] = i;
        pthread_create(&threads[i], NULL, go, &args[i]);
    }
    for (i = 0; i < NTHREADS; i++)
    {
        printf("Thread %d returned\n", i);
        pthread_join(threads[i], NULL);
    }
    printf("Main thread done.\n");
    return 0;
}

void *go(void *arg)
{
    // pass the value to the thread
    int threadId = *(int *)arg;
    printf("Hello from thread %lu with iteration %d\n", (unsigned long)pthread_self(), threadId);
    return 0;
}
