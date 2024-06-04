// Name: Sami Shibli
// Date: Tue May 7th
// Title: Lab5 – Step 3 - Using Semaphores
// Description: This program illustrates the use of semaphores to coordinate producer and
//              consumer threads accessing a shared buffer. The semaphores are used to manage
//              the number of full and empty slots in the buffer, and to ensure mutual exclusion
//              during the access of the shared buffer.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_ITEMS 20
#define BUFFER_SIZE 5 // Example buffer size, less than 10

// Buffer and buffer counters
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores and mutex lock
sem_t full;
sem_t empty;
sem_t mutex;

// Function declarations
void *producer(void *arg);
void *consumer(void *arg);

int main()
{
    pthread_t tid_producer, tid_consumer;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);           // Binary semaphore for buffer access
    sem_init(&full, 0, 0);            // Initially, buffer is empty
    sem_init(&empty, 0, BUFFER_SIZE); // Initially, buffer is empty

    pthread_create(&tid_producer, NULL, producer, NULL);
    pthread_create(&tid_consumer, NULL, consumer, NULL);

    pthread_join(tid_producer, NULL);
    pthread_join(tid_consumer, NULL);

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}

void *producer(void *arg)
{
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        int item = i; // Produce an item

        sem_wait(&empty);
        sem_wait(&mutex); // Enter critical section

        // Add the item to the buffer
        buffer[in] = item;
        printf("Producer produced item %d at %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex); // Leave critical section
        sem_post(&full);

        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg)
{
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex); // Enter critical section

        // Remove an item from the buffer
        int item = buffer[out];
        printf("Consumer consumed item %d from %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex); // Leave critical section
        sem_post(&empty);

        sleep(2);
    }
    return NULL;
}
