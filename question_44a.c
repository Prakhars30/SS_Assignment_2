// Receive a message from the message queue with 0 as flag (blocks until a message arrives)

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf_t{
    long mtype;
    char mtext[100];
};

int main(){
    struct msgbuf_t m;

    key_t key = ftok(".", 'a');
    int msgid = msgget(key, IPC_CREAT | 0666);

    printf("Waiting for a message...\n");
    if (msgrcv(msgid, &m, sizeof(m.mtext), 0, 0) == -1){
        perror("msgrcv");
        return 1;
    }

    printf("Received: %s\n", m.mtext);
    return 0;
}
