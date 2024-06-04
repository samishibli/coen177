// Name: Sami Shibli
// Date: Tue May 28th
// Title:Lab 7 pt 1

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <numRequests> <maxPageNumber>\n", argv[0]);
        return 1;
    }

    int numRequests = atoi(argv[1]);
    int maxPageNumber = atoi(argv[2]);
    FILE *fp = fopen("testInput.txt", "w");
    if (fp == NULL)
    {
        perror("Unable to open file");
        return 1;
    }

    for (int i = 0; i < numRequests; i++)
    {
        fprintf(fp, "%d\n", rand() % maxPageNumber);
    }

    fclose(fp);
    return 0;
}
