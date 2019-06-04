#include <stdio.h>
#include <time.h>
#include <unistd.h>
int main()
{
    printf("%d\n",_SC_CLK_TCK);
    printf("pgrp is %d\n",getpgrp());
    printf("sid is %d\n",getsid(getpid()));
}