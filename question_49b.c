// Protect shared memory from concurrent write access using a semaphore

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main(){
    union semun arg;
    struct sembuf p = {0, -1, 0};
    struct sembuf v = {0, 1, 0};

    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    int *counter = shmat(shmid, NULL, 0);
    *counter = 0;

    int semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);

    if (fork() == 0){
        for (int i = 0; i < 100000; i++){
            semop(semid, &p, 1);
            (*counter)++;
            semop(semid, &v, 1);
        }
        shmdt(counter);
        exit(0);
    }

    for (int i = 0; i < 100000; i++){
        semop(semid, &p, 1);
        (*counter)++;
        semop(semid, &v, 1);
    }

    wait(NULL);
    printf("Counter = %d (expected 200000)\n", *counter);

    shmdt(counter);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    return 0;
}
