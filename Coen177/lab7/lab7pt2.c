// Name: Sami Shibli
// Date: Tue May 28th
// Title:lab 7 pt2

#include <stdio.h>
#include <stdlib.h>

// Define a struct to represent a page reference
typedef struct
{
    int pageno;
} ref_page;

ref_page *cache;     // Cache that stores pages
char pageCache[100]; // Buffer to hold input from the test file
int totalFaults = 0; // Keeps track of the total page faults
int cacheSize;       // Size of the cache

// Function to initialize the cache
void initializeCache(int size)
{
    cacheSize = size;
    cache = (ref_page *)malloc(cacheSize * sizeof(ref_page));
    for (int i = 0; i < cacheSize; i++)
    {
        cache[i].pageno = -1;
    }
}

void handlePageRequest(int page_num)
{
    printf("Handling page request for page number: %d\n", page_num);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <cacheSize>\n", argv[0]);
        return 1;
    }

    cacheSize = atoi(argv[1]);
    initializeCache(cacheSize);

    while (fgets(pageCache, sizeof(pageCache), stdin))
    {
        int page_num = atoi(pageCache); // Stores number read from file as an int
        handlePageRequest(page_num);
    }

    free(cache);
    return 0;
}
