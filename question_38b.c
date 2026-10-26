// FIFO two way communication using two FIFOs - program B

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(){
    char buf[100];

    mkfifo("fifo_a2b", 0666);
    mkfifo("fifo_b2a", 0666);

    int rfd = open("fifo_a2b", O_RDONLY);
    int wfd = open("fifo_b2a", O_WRONLY);

    int n = read(rfd, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    printf("B received: %s\n", buf);

    char *reply = "Hello A, this is B";
    write(wfd, reply, strlen(reply));

    close(rfd);
    close(wfd);
    return 0;
}
