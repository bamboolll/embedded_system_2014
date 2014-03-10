#include <stdio.h>
#include <unistd.h>
int main()
{
	pid_t pid_var;
	pid_var = fork();
	printf("pid_var is: %d, mypid: %d, my parent: %d\n", pid_var, getpid(), getppid());
	return 0;
}
