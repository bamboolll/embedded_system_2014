
#include <stdio.h>    
#include <unistd.h>  
#include <signal.h>    

void catch_int(int sig_num)
{
    signal(SIGINT, catch_int);
    printf("Don't press Ctrl-C  to stop me\n");
}

int main(int argc, char* argv[])
{
     int count=0;
	pid_t my_pid = getpid();
    signal(SIGINT, catch_int);

    while (1) {
       printf("Process %d is calculating ...  %d \n",my_pid, count++);
       sleep(1);
   }
}

