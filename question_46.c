// Remove the message queue

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(){
    key_t key = ftok(".", 'a');
    int msgid = msgget(key, 0666);
    if (msgid == -1){
        perror("msgget");
        return 1;
    }

    if (msgctl(msgid, IPC_RMID, NULL) == -1){
        perror("msgctl IPC_RMID");
        return 1;
    }

    printf("Message queue %d removed\n", msgid);
    return 0;
}
