/* C program to demonstrate the creation of four processes each with a different command-line delay */
#include <stdio.h>     /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* fork, usleep */
#include <stdlib.h>    /* atoi, exit */
#include <errno.h>     /* errno */

/* main function with command-line arguments to pass */
int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Usage: %s <delay1> <delay2> <delay3> <delay4>\n", argv[0]);
        exit(0);
    }

    int delays[4];
    for (int j = 0; j < 4; j++)
    {
        delays[j] = atoi(argv[j + 1]);
    }

    pid_t pids[3];
    printf("\nBefore forking.\n");

    for (int k = 0; k < 3; k++)
    {
        pids[k] = fork();
        if (pids[k] < 0)
        {
            fprintf(stderr, "can't fork, error %d\n", errno);
            exit(0);
        }
        if (pids[k] == 0)
        { // Child process created
            for (int i = 0; i < 10; i++)
            {
                printf("I am process with PID %d using delay %d microseconds, displaying iteration %d\n", getpid(), delays[k + 1], i);
                usleep(delays[k + 1]);
            }
            exit(0);
        }
    }

    for (int i = 0; i < 10; i++)
    {
        printf("\t \t \t I am the parent process with PID %d using delay %d microseconds, displaying iteration %d \n", getpid(), delays[0], i);
        usleep(delays[0]);
    }

    for (int k = 0; k < 3; k++)
    {
        wait(NULL);
    }

    return 0;
}
