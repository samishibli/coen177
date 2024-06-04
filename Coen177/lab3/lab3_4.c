// Name: Sami Shibli
// Date: Tuesday, April 16
// Lab 2, Step 4

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int fds[2];
    pipe(fds);
    if (fork() == 0)
    {
        close(fds[0]);
        dup2(fds[1], STDOUT_FILENO);
        close(fds[1]);
        execlp("cat", "cat", "/etc/passwd", NULL);
    }
    else if (fork() == 0)
    {
        close(fds[1]);
        dup2(fds[0], STDIN_FILENO);
        close(fds[0]);
        execlp("grep", "grep", "root", NULL);
    }
    else
    {
        close(fds[0]);
        close(fds[1]);
        wait(NULL);
        wait(NULL);
    }

    return 0;
}
