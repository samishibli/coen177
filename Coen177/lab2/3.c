/* C program to demonstrate the use of fork() with command-line delay input */
#include <stdio.h>     /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* fork, usleep */
#include <stdlib.h>    /* atoi, exit */
#include <errno.h>     /* errno */

/* main function with command-line arguments to pass */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <delay>\n", argv[0]);
        exit(0);
    }

    int n = atoi(argv[1]);
    pid_t pid;
    int i;

    printf("\n Before forking.\n");
    pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if (pid)
    {
        for (i = 0; i < 10; i++)
        {
            printf("\t \t \t I am the parent Process displaying iteration %d \n", i);
            usleep(n);
        }
    }
    else
    {
        for (i = 0; i < 10; i++)
        {
            printf("I am the child process displaying iteration %d\n", i);
            usleep(n);
        }
    }
    return 0;
}
