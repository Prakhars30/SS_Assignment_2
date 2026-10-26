// Wait for SIGSTOP signal. Run this first, then run question_64b with the printed pid

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig){
    printf("Caught SIGSTOP\n");
}

int main(){
    setbuf(stdout, NULL);
    printf("pid = %d\n", getpid());

    if (signal(SIGSTOP, handler) == SIG_ERR)
        perror("signal(SIGSTOP)");      // SIGSTOP can not be caught

    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGSTOP, &sa, NULL) == -1)
        perror("sigaction(SIGSTOP)");

    while (1){
        printf("Running, waiting for SIGSTOP...\n");
        sleep(2);
    }

    return 0;
}
