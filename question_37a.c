// FIFO one way communication - writer (run this first, then run question_37b)

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(){
    mkfifo("fifo_oneway", 0666);

    printf("Waiting for a reader...\n");
    int fd = open("fifo_oneway", O_WRONLY);
    char *msg = "Hello from the writer through FIFO\n";
    write(fd, msg, strlen(msg));
    printf("Message written\n");
    close(fd);
    return 0;
}
