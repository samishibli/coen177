/* C program to demonstrate the use of fork() with command-line delay input and exec() to change the child process task to running ls */
#include <stdio.h>     /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* fork, execlp */
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

    int n = atoi(argv[1]); // n microseconds delay taken from command-line argument
    pid_t pid;
    int i;

    printf("\nBefore forking.\n");
    pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    else if (pid == 0)
    {
        // Child process: run the ls command
        execlp("/bin/ls", "ls", NULL);
        // Only reach here if execlp fails
        fprintf(stderr, "Failed to execute ls\n");
        exit(1);
    }
    else
    {
        // Parent process: wait for the child to finish
        wait(NULL);
        printf("Child has completed the task!\n");
        for (i = 0; i < 10; i++)
        {
            printf("\t \t \t I am the parent Process displaying iteration %d with delay %d microseconds\n", i, n);
            usleep(n);
        }
        exit(0);
    }
    return 0;
}
