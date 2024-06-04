// Name: Sami Shibli
// Date: Tue May 28th
// Title:LRU Algo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

typedef struct
{
    int pageno;
    int timestamp;
} ref_page;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <cacheSize>\n", argv[0]);
        return 1;
    }

    int C_SIZE = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[C_SIZE];     // Cache that stores pages
    char pageCache[100];        // Cache that holds the input from test file

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    int time = 0;        // Keeps track of the current time

    for (i = 0; i < C_SIZE; i++)
    { // initialize cache array
        cache[i].pageno = -1;
        cache[i].timestamp = 0;
    }

    while (fgets(pageCache, sizeof(pageCache), stdin))
    {
        int page_num = atoi(pageCache); // Stores number read from file as an int

        int foundInCache = 0;
        int oldest = 0;
        int oldestTime = INT_MAX;
        for (i = 0; i < C_SIZE; i++)
        {
            if (cache[i].pageno == page_num)
            {
                foundInCache = 1;
                cache[i].timestamp = time;
                break;
            }
            if (cache[i].timestamp < oldestTime)
            {
                oldest = i;
                oldestTime = cache[i].timestamp;
            }
        }

        if (!foundInCache)
        {
            printf("%d\n", page_num);
            cache[oldest].pageno = page_num;
            cache[oldest].timestamp = time;
            totalFaults++;
        }

        time++; // Increment time
    }

    return 0;
}
