// name: sami Shibli
// date: june 4 2024
// description: Header file for Step 2 - Basic File Reading

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char buffer[10000];
    FILE *fp;
    size_t bytesRead;

    fp = fopen(argv[1], "rb");
    if (fp == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fp)) > 0)
    {
        // Do nothing, just read
    }

    fclose(fp);
    return 0;
}
