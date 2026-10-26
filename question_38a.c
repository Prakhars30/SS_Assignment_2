// FIFO two way communication using two FIFOs - program A (run first, then run question_38b)

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(){
    char buf[100];

    mkfifo("fifo_a2b", 0666);
    mkfifo("fifo_b2a", 0666);

    int wfd = open("fifo_a2b", O_WRONLY);
    int rfd = open("fifo_b2a", O_RDONLY);

    char *msg = "Hello B, this is A";
    write(wfd, msg, strlen(msg));

    int n = read(rfd, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    printf("A received: %s\n", buf);

    close(wfd);
    close(rfd);
    return 0;
}
