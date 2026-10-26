// Ticket number program using a semaphore (create ticket.txt first using question_17a)

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
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
    struct sembuf p = {0, -1, 0};
    struct sembuf v = {0, 1, 0};

    key_t key = ftok(".", 's');
    int semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid != -1){
        arg.val = 1;                         // first process initializes the semaphore
        semctl(semid, 0, SETVAL, arg);
    }
    else{
        semid = semget(key, 1, 0666);
    }

    int fd = open("ticket.txt", O_RDWR);

    printf("Waiting to enter critical section...\n");
    semop(semid, &p, 1);                     // lock
    printf("Inside critical section\n");

    char buf[10];
    int n = read(fd, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    int ticket = atoi(buf) + 1;
    printf("New ticket number: %d\n", ticket);
    sleep(10);

    lseek(fd, 0, SEEK_SET);
    char out[20];
    sprintf(out, "%d", ticket);
    write(fd, out, strlen(out));

    semop(semid, &v, 1);                     // unlock
    printf("Left critical section\n");
    close(fd);
    return 0;
}
