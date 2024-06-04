/* C program to demonstrate the use of fork()*/

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
#include <sys/wait.h>

/* main function */
int main(int argc, char* argv[]){
    pid_t pid;
    int i, n;

    printf("Before Forking\n");
    pid = fork();
    if(pid < 0){
        fprintf(stderr, "Error, Can't Fork: %d\n", errno);
    }

    if(pid == 0){
        execlp("/bin/ls", "ls", NULL);
    }
    else{
        wait(NULL);
        printf("Child Complete\n");
    }

}