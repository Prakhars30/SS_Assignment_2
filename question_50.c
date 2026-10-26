// Induce a deadlock using two semaphores. Process 1 takes S0 then S1, process 2 takes S1 then S0

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
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

int semid;
pid_t child;

void on_alarm(int sig){
    printf("Deadlock: both processes are blocked forever waiting for each other\n");
    kill(child, SIGKILL);
    semctl(semid, 0, IPC_RMID);
    exit(1);
}

int main(){
    setbuf(stdout, NULL);
    union semun arg;
    struct sembuf p0 = {0, -1, 0}, p1 = {1, -1, 0};

    semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);
    semctl(semid, 1, SETVAL, arg);

    child = fork();
    if (child == 0){
        semop(semid, &p1, 1);
        printf("Child holds S1, wants S0\n");
        sleep(2);
        semop(semid, &p0, 1);           // blocks forever
        printf("Child got both\n");
        return 0;
    }

    signal(SIGALRM, on_alarm);
    semop(semid, &p0, 1);
    printf("Parent holds S0, wants S1\n");
    sleep(2);
    alarm(5);                           // only to report the deadlock and clean up
    semop(semid, &p1, 1);               // blocks forever
    printf("Parent got both\n");
    return 0;
}
