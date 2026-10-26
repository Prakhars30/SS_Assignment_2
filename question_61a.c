// Catch SIGSEGV using the sigaction system call

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define MSG(s) write(1, s, sizeof(s) - 1)

void handler(int sig){
    MSG("Caught SIGSEGV (segmentation fault)\n");
    _exit(1);
}

int main(){
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGSEGV, &sa, NULL);

    int *p = NULL;
    *p = 10;

    return 0;
}
