// Create a counting semaphore and initialize its value to 5

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

    key_t key = ftok(".", 'd');
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1){
        perror("semget");
        return 1;
    }

    arg.val = 5;
    semctl(semid, 0, SETVAL, arg);

    printf("Counting semaphore created, id = %d, value = %d\n", semid, semctl(semid, 0, GETVAL));
    return 0;
}
