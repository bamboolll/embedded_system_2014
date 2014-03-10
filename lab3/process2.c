#include <stdio.h>
#include <unistd.h>
int main()
{
	printf("Calling ps –f --------------\n");
	execl("/bin/ps", "ps", "-f", (char *)NULL);
	printf("End calling --------------\n");
	return 0;
}
