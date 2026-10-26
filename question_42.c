// Print information about a message queue using msqid_ds and ipc_perm structures

#include <stdio.h>
#include <time.h>
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

    if (msgctl(msgid, IPC_STAT, &ds) == -1){
        perror("msgctl");
        return 1;
    }

    printf("Access permission : %o\n", ds.msg_perm.mode & 0777);
    printf("UID               : %d\n", ds.msg_perm.uid);
    printf("GID               : %d\n", ds.msg_perm.gid);
    printf("Last message sent : %s", ds.msg_stime ? ctime(&ds.msg_stime) : "no message sent yet\n");
    printf("Last msg received : %s", ds.msg_rtime ? ctime(&ds.msg_rtime) : "no message received yet\n");
    printf("Last change       : %s", ctime(&ds.msg_ctime));
    printf("Size of queue     : %lu bytes\n", (unsigned long)ds.msg_cbytes);
    printf("No. of messages   : %lu\n", (unsigned long)ds.msg_qnum);
    printf("Max bytes allowed : %lu\n", (unsigned long)ds.msg_qbytes);
    printf("PID of msgsnd     : %d\n", ds.msg_lspid);
    printf("PID of msgrcv     : %d\n", ds.msg_lrpid);
    return 0;
}
