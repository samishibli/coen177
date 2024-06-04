#include <stdio.h>   // For printf, stderr
#include <stdlib.h>  // For atoi, exit
#include <unistd.h>  // For usleep
#include <pthread.h> // For pthread_create, pthread_join

void *threadMethod(void *n)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("I am the child process displaying iteration %d\n", i);
        usleep(*(int *)n);
    }
    pthread_exit(0);
}
int main(int argc, char *argv[])
{
    pid_t pid;
    int i, n;
    n = atoi(argv[1]);
    printf("Before Thread Creation\n");
    pthread_t id;
    pthread_create(&id, NULL, threadMethod, &n);
    for (i = 0; i < 10; i++)
    {
        printf("\t \t \tI am the parent process displaying iteration %d\n, i");
        usleep(n);
    }
    pthread_join(id, NULL);
    return 0;
}
