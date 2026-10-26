// Catch SIGFPE using the sigaction system call

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define MSG(s) write(1, s, sizeof(s) - 1)

void handler(int sig){
    MSG("Caught SIGFPE (divide by zero)\n");
    _exit(1);
}

int main(){
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGFPE, &sa, NULL);

    volatile int a = 10, b = 0;
    int c = a / b;
    printf("%d\n", c);

    return 0;
}
