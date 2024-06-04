// Name: Sami Shibli
// Date: Tuesday, April 16
// Lab 2, Step 6: Producer-Consumer using Shared Memory

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SIZE 1024

struct info
{
    char data[SIZE];
};

int main()
{
    int id;
    struct info *ctrl;
    char input[SIZE];

    printf("Enter a sentence for the producer to send: ");
    fgets(input, SIZE, stdin);

    // Create shared memory
    key_t key = ftok("shmfile", 65);
    id = shmget(key, sizeof(struct info), IPC_CREAT | 0666);
    if (id < 0)
    {
        perror("shmget");
        exit(1);
    }

    if (fork() == 0)
    {

        ctrl = (struct info *)shmat(id, 0, 0);
        strncpy(ctrl->data, input, SIZE);
        shmdt(ctrl);
        exit(0);
    }
    else
    {
        wait(NULL);
        ctrl = (struct info *)shmat(id, 0, 0);
        printf("Consumer received: %s", ctrl->data);
        shmdt(ctrl);
        shmctl(id, IPC_RMID, NULL);
    }

    return 0;
}
