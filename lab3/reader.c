#include <string.h>
#include <stdio.h>      
#include <stdlib.h>    
#include <unistd.h>   
#include <sys/types.h>   
#include <sys/ipc.h>     
#include <sys/msg.h>     

#define QUEUE_ID 137      
#define MAX_MSG_SIZE 200 
#define NUM_MESSAGES 100 

struct msgbuf{  long int mtype;  char mtext[1]; };

int main(int argc, char *argv[]){
    int queue_id, rc, msg_type;     
    struct msgbuf* msg;  
	
    msg_type = atoi(argv[1]);
    if (msg_type < 1 || msg_type > 3) {
        fprintf(stderr, "Usage: %s <message type>\n", argv[0]);
        fprintf(stderr, "       <message type> must be between 1 and 3.\n");
  	    exit(1);
    }
    queue_id = msgget(QUEUE_ID, 0);
    printf("message queue opened, queue id '%d'.\n", queue_id);
    msg = (struct msgbuf*)malloc(sizeof(struct msgbuf)+MAX_MSG_SIZE);
    while (1) {
      rc = msgrcv(queue_id, msg, MAX_MSG_SIZE+1, msg_type, 0);
  	  printf("Reader '%d' read message: '%s'\n", msg_type, msg->mtext);
      sleep(1);
    }
   return 0;
}

