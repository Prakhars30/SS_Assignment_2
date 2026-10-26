// Execute ls -l | wc using dup2

#include <unistd.h>
#include <sys/wait.h>

int main(){
    int fd[2];
    pipe(fd);

    if (fork() == 0){
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        execlp("ls", "ls", "-l", (char *)NULL);
    }

    if (fork() == 0){
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        execlp("wc", "wc", (char *)NULL);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
