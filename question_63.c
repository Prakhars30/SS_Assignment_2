// Create an orphan process. The child sends SIGKILL to its parent using kill, so the child becomes an orphan

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(){
    setbuf(stdout, NULL);

    pid_t pid = fork();

    if (pid == 0){
        printf("Child : pid = %d, parent pid = %d\n", getpid(), getppid());
        sleep(1);       // let the parent print its message first
        printf("Child : sending SIGKILL to parent\n");
        kill(getppid(), SIGKILL);

        sleep(2);       // give the kernel time to re-parent the child
        printf("Child : now an orphan, new parent pid = %d (init/systemd)\n", getppid());
    }
    else{
        printf("Parent: pid = %d, waiting to be killed...\n", getpid());
        while (1)
            sleep(1);
    }

    return 0;
}
