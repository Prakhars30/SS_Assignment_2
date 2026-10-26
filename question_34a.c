// Execute ls -l | wc using dup

#include <unistd.h>
#include <sys/wait.h>

int main(){
    int fd[2];
    pipe(fd);

    if (fork() == 0){
        close(fd[0]);
        close(1);
        dup(fd[1]);         // lowest free descriptor (1) now refers to the write end
        close(fd[1]);
        execlp("ls", "ls", "-l", (char *)NULL);
    }

    if (fork() == 0){
        close(fd[1]);
        close(0);
        dup(fd[0]);         // lowest free descriptor (0) now refers to the read end
        close(fd[0]);
        execlp("wc", "wc", (char *)NULL);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
