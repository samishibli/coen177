// name: sami Shibli
// date: june 4 2024
// description: Header file for Step 5 - Concurrent Read and Write with Multiple Threads

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    char *filename;
    size_t buffer_size;
    int thread_id;
} ThreadData;

void *copy_file(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    char *filename = data->filename;
    size_t buffer_size = data->buffer_size;
    int thread_id = data->thread_id;

    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL)
    {
        perror("Failed to allocate buffer");
        pthread_exit(NULL);
    }

    FILE *input_fp = fopen(filename, "rb");
    if (input_fp == NULL)
    {
        perror("Error opening input file");
        free(buffer);
        pthread_exit(NULL);
    }

    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "output_%d.txt", thread_id);

    FILE *output_fp = fopen(output_filename, "wb");
    if (output_fp == NULL)
    {
        perror("Error opening output file");
        fclose(input_fp);
        free(buffer);
        pthread_exit(NULL);
    }

    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, buffer_size, input_fp)) > 0)
    {
        fwrite(buffer, 1, bytesRead, output_fp);
    }

    fclose(input_fp);
    fclose(output_fp);
    free(buffer);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <filename> <buffer_size> <num_threads>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    size_t buffer_size = atoi(argv[2]);
    int num_threads = atoi(argv[3]);

    if (buffer_size <= 0 || num_threads <= 0)
    {
        fprintf(stderr, "Invalid buffer size or number of threads\n");
        return 1;
    }

    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    for (int i = 0; i < num_threads; i++)
    {
        thread_data[i].filename = filename;
        thread_data[i].buffer_size = buffer_size;
        thread_data[i].thread_id = i;

        int rc = pthread_create(&threads[i], NULL, copy_file, &thread_data[i]);
        if (rc)
        {
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
