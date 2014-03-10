#include <stdio.h>      
#include <stdlib.h>   
#include <string.h>    
#include <sys/types.h>  
#include <sys/ipc.h>     
#include <sys/msg.h>    

#define QUEUE_ID 137      
#define MAX_MSG_SIZE 200 
#define NUM_MESSAGES 100

struct msgbuf {
   long int mtype;
   char mtext[1];
};
int main(int argc, char* argv[]){
    int queue_id;             
    struct msgbuf* msg;  
	int i,rc;       
    queue_id = msgget(QUEUE_ID, IPC_CREAT |  0777);
    printf("message queue created, queue id '%d'.\n", queue_id);
    msg = (struct msgbuf*)malloc(sizeof(struct msgbuf)+MAX_MSG_SIZE);
    for (i=1; i <= NUM_MESSAGES; i++) {
        msg->mtype = (i % 3) + 1; 
        sprintf(msg->mtext, "hello world - %d", i);
        msgsnd(queue_id, msg, strlen(msg->mtext)+1, 0);
    }
    free(msg);
    printf("generated %d messages, exiting.\n",NUM_MESSAGES);
    return 0;
}

