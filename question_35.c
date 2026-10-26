// Find the total number of directories in pwd using ls -l | grep ^d | wc (only dup2 used)

#include <unistd.h>
#include <sys/wait.h>

int main(){
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);

    if (fork() == 0){
        dup2(p1[1], 1);
        close(p1[0]); close(p1[1]); close(p2[0]); close(p2[1]);
        execlp("ls", "ls", "-l", (char *)NULL);
    }

    if (fork() == 0){
        dup2(p1[0], 0);
        dup2(p2[1], 1);
        close(p1[0]); close(p1[1]); close(p2[0]); close(p2[1]);
        execlp("grep", "grep", "^d", (char *)NULL);
    }

    if (fork() == 0){
        dup2(p2[0], 0);
        close(p1[0]); close(p1[1]); close(p2[0]); close(p2[1]);
        execlp("wc", "wc", (char *)NULL);
    }

    close(p1[0]); close(p1[1]); close(p2[0]); close(p2[1]);
    wait(NULL);
    wait(NULL);
    wait(NULL);
    return 0;
}
