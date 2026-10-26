// Create a message queue and print the key and message queue id

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(){
    key_t key = ftok(".", 'a');
    if (key == -1){
        perror("ftok");
        return 1;
    }

    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1){
        perror("msgget");
        return 1;
    }

    printf("Key = %d (0x%x)\n", key, key);
    printf("Message queue id = %d\n", msgid);
    return 0;
}
