// Protect two pseudo resources using a counting semaphore (initial value 2)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main(){
    setbuf(stdout, NULL);
    union semun arg;
    struct sembuf p = {0, -1, 0};
    struct sembuf v = {0, 1, 0};

    int semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    arg.val = 2;                       // two resources available
    semctl(semid, 0, SETVAL, arg);

    for (int i = 1; i <= 4; i++){
        if (fork() == 0){
            printf("Process %d (pid %d) waiting for a resource\n", i, getpid());
            semop(semid, &p, 1);
            printf("Process %d got a resource\n", i);
            sleep(3);
            printf("Process %d released the resource\n", i);
            semop(semid, &v, 1);
            exit(0);
        }
    }

    for (int i = 0; i < 4; i++)
        wait(NULL);

    semctl(semid, 0, IPC_RMID);
    return 0;
}
