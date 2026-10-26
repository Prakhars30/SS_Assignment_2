// Execute ls -l | wc using fcntl

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(){
    int fd[2];
    pipe(fd);

    if (fork() == 0){
        close(fd[0]);
        close(1);
        fcntl(fd[1], F_DUPFD, 0);   // duplicates to the lowest free descriptor >= 0, i.e. 1
        close(fd[1]);
        execlp("ls", "ls", "-l", (char *)NULL);
    }

    if (fork() == 0){
        close(fd[1]);
        close(0);
        fcntl(fd[0], F_DUPFD, 0);   // lowest free descriptor is 0
        close(fd[0]);
        execlp("wc", "wc", (char *)NULL);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
