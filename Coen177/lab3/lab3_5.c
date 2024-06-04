// Name: Sami Shibli
// Date: Tuesday, April 16
// Lab 2, Step 5: Producer-Consumer using Pipes

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main()
{
    int fds[2];
    char buff[BUFFER_SIZE];
    char input[BUFFER_SIZE];
    int count;

    printf("Enter a sentence for the producer to send: ");
    fgets(input, BUFFER_SIZE, stdin);

    pipe(fds);

    if (fork() == 0)
    {
        close(fds[0]);
        write(fds[1], input, strlen(input) + 1);
        close(fds[1]);
        exit(0);
    }
    else
    {
        close(fds[1]);
        count = read(fds[0], buff, BUFFER_SIZE);
        if (count > 0)
            printf("Consumer received: %s", buff);

        close(fds[0]);
        wait(0);
    }

    return 0;
}
