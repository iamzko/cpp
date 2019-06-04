#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
	pid_t a;
	a = getpid();
	printf("pid is %d\n", a);
	a = getppid();
	printf("ppid is %d\n", a);
	uid_t b;
	b = getuid();
	printf("uid is %d\n", b);
	b = geteuid();
	printf("euid is %d\n", b);
	gid_t c;
	c = getgid();
	printf("gid is %d\n", c);
	c = getegid();
	printf("egid is %d\n", c);
	if ((a = fork()) < 0)
	{
		printf("fork error!\n");
	}
	else if (a == 0)
	{
		printf("this is child!\n");
		printf("child pid is %d\n", getpid());
		sleep(5);
		_exit(0);
	}
	else
	{

		printf("this is father and child pid is %d\n",a);
	}
	pid_t d;
	if ((d = vfork()) < 0)
	{
		printf("error vfork!\n");
	}
	else if (d == 0)
	{
		printf("this is vfork child!\n");
		printf("vfork pid is %d\n", getpid());
		sleep(20);
		_exit(0);
	}
	printf("d is %d \n",d);

	printf("where is here?%d\n",getpid());
}
