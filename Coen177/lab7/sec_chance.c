// Name: Sami Shibli
// Date: Tue May 28th
// Title:second chance Algo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
    int pageno;
    int reference_bit; // Reference bit for the second chance algorithm
} ref_page;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <cacheSize>\n", argv[0]);
        return 1;
    }

    int C_SIZE = atoi(argv[1]);
    ref_page cache[C_SIZE];
    char pageCache[100];

    int i;
    int totalFaults = 0;
    int pointer = 0;

    for (i = 0; i < C_SIZE; i++)
    { // initialize cache array
        cache[i].pageno = -1;
        cache[i].reference_bit = 0;
    }

    while (fgets(pageCache, sizeof(pageCache), stdin))
    {
        int page_num = atoi(pageCache);

        int foundInCache = 0;
        for (i = 0; i < C_SIZE; i++)
        {
            if (cache[i].pageno == page_num)
            {
                foundInCache = 1;
                cache[i].reference_bit = 1;
                break;
            }
        }

        if (!foundInCache)
        {

            printf("%d\n", page_num);
            while (cache[pointer].reference_bit == 1)
            {
                cache[pointer].reference_bit = 0;
                pointer = (pointer + 1) % C_SIZE;
            }
            // Replace the page at the pointer
            cache[pointer].pageno = page_num;
            totalFaults++;
            pointer = (pointer + 1) % C_SIZE;
        }
    }

    return 0;
}
