// Receive a message from the message queue with IPC_NOWAIT as flag (does not block)

#include <stdio.h>
#include <errno.h>
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

    if (msgrcv(msgid, &m, sizeof(m.mtext), 0, IPC_NOWAIT) == -1){
        if (errno == ENOMSG)
            printf("No message in the queue\n");
        else
            perror("msgrcv");
        return 1;
    }

    printf("Received: %s\n", m.mtext);
    return 0;
}
