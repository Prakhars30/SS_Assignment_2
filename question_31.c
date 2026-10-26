// Create a pipe, write to the pipe, read from the pipe and display the content on the monitor

#include <stdio.h>
#include <unistd.h>

int main(){
    int fd[2];
    char buf[50];

    if (pipe(fd) == -1){
        perror("pipe");
        return 1;
    }

    write(fd[1], "Hello through the pipe\n", 23);

    int n = read(fd[0], buf, sizeof(buf) - 1);
    buf[n] = '\0';

    printf("Content read from pipe: %s", buf);

    close(fd[0]);
    close(fd[1]);
    return 0;
}
