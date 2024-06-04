/* C program to demonstrate the use of fork()*/

#include <stdio.h>     /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* fork */
#include <stdlib.h>    /* atoi */
#include <errno.h>     /* errno */
#include <sys/wait.h>
#include <pthread.h>

struct data
{
    int n;
    int tid;
};

void *threadfunc(void *data)
{
    int i;
    struct data a = *(struct data *)data;
    if (a.tid == 1)
    {
        for (int i = 0; i < 10; i++)
        {
            printf("I am the parent process displaying iteration %d\n", i);
            usleep(a.n);
        }
    }
    else
    {
        for (i = 0; i < 10; i++)
        {
            printf("\t \t \tI am the child process displaying iteration %d\n", i);
        }
    }

    pthread_exit(0);
}

/* main function */
int main(int argc, char *argv[])
{
    pid_t pid;
    int i;
    int n = atoi(argv[1]);
    pthread_t threads[2];
    printf("Before Thread\n");
    struct data data1, data2;
    // pthread_t tid1, tid2;
    data1.n = n;
    data2.n = n;
    data1.tid = 1;
    data2.tid = 2;
    pthread_create(&threads[0], NULL, threadfunc, &data1);
    pthread_create(&threads[1], NULL, threadfunc, &data2);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    pthread_exit(NULL);
    return 0;
}