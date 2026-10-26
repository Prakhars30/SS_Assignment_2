// Remove the semaphore created by question_49a

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(){
    key_t key = ftok(".", 's');
    int semid = semget(key, 1, 0666);
    if (semid == -1){
        perror("semget");
        return 1;
    }

    if (semctl(semid, 0, IPC_RMID) == -1){
        perror("semctl IPC_RMID");
        return 1;
    }

    printf("Semaphore %d removed\n", semid);
    return 0;
}
