#include <stdio.h>
#include <pthread.h>
void * thread_func(void *arg)
{
	int *t = (int *)arg;
	printf("Thread0, arg = %d\n", *t);
	sleep(5);
	pthread_exit(NULL); 
}
int main()
{
	pthread_t thread0;
	int ret;
	int a = 10;
	ret = pthread_create(&thread0, NULL, thread_func, &a);
	if(ret != 0) printf("cannot create thread\n");
	pthread_join(thread0, NULL);
	printf("Exit main\n");
	return 0;
}
