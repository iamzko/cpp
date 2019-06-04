#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    static int m = 0;
    pid_t pid;
    if((pid = fork())<0)
    {
        printf("error when fork\n");
    }
    else if(pid == 0)
    {
        printf("m is now %d\n",m++);
        if(execl("./a.out","",NULL) < 0)
        {
            printf("execl error!\n");
        }
    }
    sleep(1);
    exit(0);
}