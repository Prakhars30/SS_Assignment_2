// Send data from the parent process to the child process using a pipe

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    int fd[2];
    char buf[100];
    pipe(fd);

    if (fork() == 0){
        close(fd[1]);
        int n = read(fd[0], buf, sizeof(buf) - 1);
        buf[n] = '\0';
        printf("Child received: %s\n", buf);
        close(fd[0]);
        return 0;
    }

    close(fd[0]);
    char *msg = "Message from parent";
    write(fd[1], msg, strlen(msg));
    close(fd[1]);
    wait(NULL);
    return 0;
}
