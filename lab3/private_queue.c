#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


struct msgbuf{
  long int mtype;
  char mtext[1];
} ;

int main(int argc, char* argv[])
{
    int queue_id = msgget(IPC_PRIVATE, 0600);

    struct msgbuf* msg;
    struct msgbuf* recv_msg;
    int rc;

    if (queue_id == -1) {
	   perror("main: msgget error ");
	   exit(1);
    }
    printf("message queue created, queue id '%d'.\n",
                                                                                      queue_id);
    msg = (struct msgbuf*)malloc(sizeof(
                     struct msgbuf)+strlen("hello world"));
    msg->mtype = 1;
    strcpy(msg->mtext, "hello world");

    rc = msgsnd(queue_id, msg, strlen(msg->mtext)+1, 0);
    if (rc == -1) {
  	     perror("main: msgsnd error");
	     exit(1);
    }
    free(msg);

    printf("message placed on the queue successfully.\n");


    recv_msg = (struct msgbuf*)malloc(sizeof(
                     struct msgbuf)+strlen("hello world"));

    rc = msgrcv(queue_id, recv_msg,
                                    strlen("hello world")+1, 0, 0);
    if (rc == -1) {
	     perror("main: msgrcv error");
	     exit(1);
    }
    printf("msgrcv: received message: mtype '%d'; mtext '%s'\n",recv_msg->mtype, recv_msg->mtext);
    
    return 0;
}

