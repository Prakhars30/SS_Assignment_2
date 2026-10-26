// Catch SIGALRM using the alarm system call

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define MSG(s) write(1, s, sizeof(s) - 1)

void handler(int sig){
    MSG("Caught SIGALRM (alarm expired)\n");
}

int main(){
    setbuf(stdout, NULL);
    signal(SIGALRM, handler);

    printf("Alarm set for 3 seconds\n");
    alarm(3);
    pause();

    return 0;
}
