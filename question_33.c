// Two way communication between parent and child using two pipes

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    int p2c[2], c2p[2];
    char buf[100];
    pipe(p2c);
    pipe(c2p);

    if (fork() == 0){
        close(p2c[1]);
        close(c2p[0]);
        int n = read(p2c[0], buf, sizeof(buf) - 1);
        buf[n] = '\0';
        printf("Child received: %s\n", buf);
        char *reply = "Hello parent, this is child";
        write(c2p[1], reply, strlen(reply));
        close(p2c[0]);
        close(c2p[1]);
        return 0;
    }

    close(p2c[0]);
    close(c2p[1]);
    char *msg = "Hello child, this is parent";
    write(p2c[1], msg, strlen(msg));
    int n = read(c2p[0], buf, sizeof(buf) - 1);
    buf[n] = '\0';
    printf("Parent received: %s\n", buf);
    close(p2c[1]);
    close(c2p[0]);
    wait(NULL);
    return 0;
}
