// Wait for data to be written into a FIFO for 10 seconds using select
// Run this, then from another terminal: echo hello > fifo_select

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/select.h>

int main(){
    char buf[100];
    fd_set rfds;
    struct timeval tv;

    mkfifo("fifo_select", 0666);
    int fd = open("fifo_select", O_RDONLY | O_NONBLOCK);

    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);
    tv.tv_sec = 10;
    tv.tv_usec = 0;

    printf("Waiting for data in FIFO for 10 seconds...\n");
    int ret = select(fd + 1, &rfds, NULL, NULL, &tv);

    if (ret == -1){
        perror("select");
    }
    else if (ret == 0){
        printf("No data was written within 10 seconds\n");
    }
    else{
        int n = read(fd, buf, sizeof(buf) - 1);
        buf[n] = '\0';
        printf("Data is available: %s", buf);
    }

    close(fd);
    return 0;
}
