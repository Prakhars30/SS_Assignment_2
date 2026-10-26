// Create a binary semaphore and initialize its value to 1

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main(){
    union semun arg;

    key_t key = ftok(".", 'c');
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1){
        perror("semget");
        return 1;
    }

    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);

    printf("Binary semaphore created, id = %d, value = %d\n", semid, semctl(semid, 0, GETVAL));
    return 0;
}
