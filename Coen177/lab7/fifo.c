// Name: Sami Shibli
// Date: Tue May 28th
// Title:FIFO Algo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
    int pageno;
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
    int totalFaults = 0;  // keeps track of the total page faults
    int placeInArray = 0; // to track the position for FIFO replacement

    for (i = 0; i < C_SIZE; i++)
    { // initialize cache array
        cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin))
    {
        int page_num = atoi(pageCache);

        // FIFO Page Replacement Implementation
        int foundInCache = 0;
        for (i = 0; i < C_SIZE; i++)
        {
            if (cache[i].pageno == page_num)
            {
                foundInCache = 1;
                break;
            }
        }

        if (!foundInCache)
        {
            printf("%d\n", page_num);
            cache[placeInArray].pageno = page_num;
            totalFaults++;
            placeInArray = (placeInArray + 1) % C_SIZE;
        }
    }

    return 0;
}
