// Change the permissions of an existing message queue using msqid_ds structure

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(){
    struct msqid_ds ds;

    key_t key = ftok(".", 'a');
    int msgid = msgget(key, 0666);
    if (msgid == -1){
        perror("msgget");
        return 1;
    }

    msgctl(msgid, IPC_STAT, &ds);
    printf("Old permission: %o\n", ds.msg_perm.mode & 0777);

    ds.msg_perm.mode = 0600;
    if (msgctl(msgid, IPC_SET, &ds) == -1){
        perror("msgctl IPC_SET");
        return 1;
    }

    msgctl(msgid, IPC_STAT, &ds);
    printf("New permission: %o\n", ds.msg_perm.mode & 0777);
    return 0;
}
