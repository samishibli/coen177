/* C program to demonstrate the use of fork()*/

#include <stdio.h>     /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* fork */
#include <stdlib.h>    /* atoi */
#include <errno.h>     /* errno */
#include <sys/wait.h>

/* main function */
int main(int argc, char *argv[])
{

    pid_t pid1, pid2;
    int i; // n is a delay in microseconds inserted in parent and child iterations

    int n[4] = {atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4])};

    printf("\n Before forking.\n");

    pid1 = fork();
    if (pid1 < 0)
    {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }

    pid2 = fork();
    if (pid2 < 0)
    {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }

    if (pid1 && pid2)
    {
        // Parent process: pid is > 0
        for (i = 0; i < 10; i++)
        {
            printf("\t \t \t I am the parent Process displaying iteration %d \n", i);
            usleep(n[0]);
        }
        wait(NULL);
        wait(NULL);
    }
    else if (pid1 && ~pid2)
    {
        // Child process: pid = 0
        for (i = 0; i < 10; i++)
        {
            printf("I am the child process displaying iteration %d\n", i);
            usleep(n[1]);
        }
        }
    else if (~pid1 && pid2)
    {
        // Parent process: pid is > 0
        for (i = 0; i < 10; i++)
        {
            printf("\t \t \t I am the child Process displaying iteration %d \n", i);
            usleep(n[2]);
        }
        wait(NULL);
    }
    else
    {
        // Child process: pid = 0
        for (i = 0; i < 10; i++)
        {
            printf("I am the child process displaying iteration %d\n", i);
            usleep(n[3]);
        }
    }

    return 0;
}