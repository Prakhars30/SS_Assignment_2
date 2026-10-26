// Print the maximum number of files that can be opened within a process and the size of a pipe (circular buffer)

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int fd[2];
    pipe(fd);

    printf("Maximum number of files a process can open: %ld\n", sysconf(_SC_OPEN_MAX));
    printf("Atomic write size of pipe (PIPE_BUF): %ld bytes\n", fpathconf(fd[0], _PC_PIPE_BUF));
    printf("Size of pipe (circular buffer): %d bytes\n", fcntl(fd[0], F_GETPIPE_SZ));

    close(fd[0]);
    close(fd[1]);
    return 0;
}
