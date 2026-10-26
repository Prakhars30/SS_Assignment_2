// Shared memory: write data, attach read only and try to overwrite, detach and remove

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main(){
    setbuf(stdout, NULL);
    key_t key = ftok(".", 'b');
    int shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if (shmid == -1){
        perror("shmget");
        return 1;
    }

    // attach with read/write and write some data
    char *ptr = shmat(shmid, NULL, 0);
    strcpy(ptr, "Data written to shared memory");
    printf("Written: %s\n", ptr);

    // attach read only (SHM_RDONLY) in a child and try to overwrite
    if (fork() == 0){
        char *ro = shmat(shmid, NULL, SHM_RDONLY);
        printf("Child (read only) reads: %s\n", ro);
        printf("Child trying to overwrite...\n");
        fflush(stdout);
        strcpy(ro, "Overwritten");
        printf("Child overwrite succeeded\n");
        exit(0);
    }

    int status;
    wait(&status);
    if (WIFSIGNALED(status))
        printf("Overwrite NOT possible, child killed by signal %d (SIGSEGV)\n", WTERMSIG(status));
    printf("Data still in shared memory: %s\n", ptr);

    shmdt(ptr);                         // detach
    shmctl(shmid, IPC_RMID, NULL);      // remove
    printf("Shared memory detached and removed\n");
    return 0;
}
