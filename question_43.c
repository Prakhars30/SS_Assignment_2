// Send messages to the message queue. Verify using: ipcs -q

#include <stdio.h>
#include <string.h>
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
    if (msgid == -1){
        perror("msgget");
        return 1;
    }

    m.mtype = 1;
    printf("Enter message: ");
    fgets(m.mtext, sizeof(m.mtext), stdin);
    m.mtext[strcspn(m.mtext, "\n")] = '\0';

    if (msgsnd(msgid, &m, strlen(m.mtext) + 1, 0) == -1){
        perror("msgsnd");
        return 1;
    }

    printf("Message sent. Check with: ipcs -q\n");
    return 0;
}
