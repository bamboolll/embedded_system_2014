#include <stdio.h>    
#include <unistd.h>  
#include <signal.h>    

int main(int argc, char* argv[])
{
	int count =0;
    pid_t my_pid = getpid();
    while (1) {
       printf("Process %d is calculating ...  %d \n",my_pid, count++);
       sleep(1);
   }
}
