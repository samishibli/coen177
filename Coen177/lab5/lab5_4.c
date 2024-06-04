// Name: Sami Shibli
// Date: Tue May 7th
// Title: Lab5 – Step 4 - Using Condition Variables
// Description: This program implements the producer-consumer problem using condition variables
//              to efficiently synchronize access to a shared buffer. It demonstrates how producers
//              and consumers can operate on a shared buffer without busy waiting, by sleeping
//              and waking up appropriately based on the buffer's state.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 10
#define NUM_ITEMS 20

// Buffer where items are stored
int buffer[MAX_BUFFER_SIZE];
int fill_idx = 0;
int use_idx = 0;
int count = 0; // Number of items in the buffer

// Thread synchronization primitives
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

// Function declarations
void put(int value)
{
    buffer[fill_idx] = value;
    fill_idx = (fill_idx + 1) % MAX_BUFFER_SIZE;
    count++;
}

int get()
{
    int tmp = buffer[use_idx];
    use_idx = (use_idx + 1) % MAX_BUFFER_SIZE;
    count--;
    return tmp;
}

void *producer(void *arg)
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        pthread_mutex_lock(&mutex);
        while (count == MAX_BUFFER_SIZE) // Wait while the buffer is full
            pthread_cond_wait(&empty, &mutex);

        put(i); // Add an item to the buffer
        printf("Produced %d\n", i);

        pthread_cond_signal(&full); // Signal that at least one item is available
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumer(void *arg)
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        pthread_mutex_lock(&mutex);
        while (count == 0) // Wait while the buffer is empty
            pthread_cond_wait(&full, &mutex);

        int item = get(); // Remove an item from the buffer
        printf("Consumed %d\n", item);

        pthread_cond_signal(&empty); // Signal that at least one space is available
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_t producer_thread, consumer_thread;

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for both threads to complete
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Cleanup resources
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);

    return 0;
}
