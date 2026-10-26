// FIFO one way communication - reader

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(){
    char buf[100];

    mkfifo("fifo_oneway", 0666);

    int fd = open("fifo_oneway", O_RDONLY);
    int n = read(fd, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    printf("Reader received: %s", buf);
    close(fd);
    return 0;
}
