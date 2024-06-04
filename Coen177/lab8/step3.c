// name: sami Shibli
// date: june 4 2024
// description: Header file for Step 3 - Variable Buffer Sizes

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <filename> <buffer_size>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    size_t buffer_size = atoi(argv[2]);

    if (buffer_size <= 0)
    {
        fprintf(stderr, "Invalid buffer size\n");
        return 1;
    }

    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL)
    {
        perror("Failed to allocate buffer");
        return 1;
    }

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        perror("Error opening file");
        free(buffer);
        return 1;
    }

    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, buffer_size, fp)) > 0)
    {
        // Do nothing, just read
    }

    fclose(fp);
    free(buffer);
    return 0;
}
