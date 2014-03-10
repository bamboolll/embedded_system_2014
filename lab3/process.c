#include <stdio.h>
#include <unistd.h>
int main()
{
	printf("Calling ps –f --------------\n");
	system("ps –f");
	printf("End calling --------------\n");
	return 0;
}
