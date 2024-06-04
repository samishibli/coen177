/* C program to create 5 processes including the parent, each with a different delay specified by command-line arguments */
#include <stdio.h>     /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* fork, usleep */
#include <stdlib.h>    /* atoi, exit */
#include <errno.h>     /* errno */

/* main function with command-line arguments to pass */
int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        printf("Usage: %s <delay1> <delay2> <delay3> <delay4> <delay5>\n", argv[0]);
        exit(0);
    }

    int delays[5];
    for (int j = 0; j < 5; j++)
    {
        delays[j] = atoi(argv[j + 1]);
    }

    pid_t pid;
    int i;

    printf("\nBefore forking.\n");

    for (i = 0; i < 4; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            fprintf(stderr, "can't fork, error %d\n", errno);
            exit(0);
        }
        if (pid == 0)
        {
            break;
        }
    }

    for (int k = 0; k < 10; k++)
    {
        printf("Process %d with PID %d using delay %d microseconds, displaying iteration %d\n", i, getpid(), delays[i], k);
        usleep(delays[i]);
    }

    if (pid > 0)
    {
        for (i = 0; i < 4; i++)
        {
            wait(NULL);
        }
    }

    return 0;
}
