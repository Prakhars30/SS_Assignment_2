// Catch SIGINT using the sigaction system call (press Ctrl+C)

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define MSG(s) write(1, s, sizeof(s) - 1)

void handler(int sig){
    MSG("Caught SIGINT (Ctrl+C)\n");
    _exit(0);
}

int main(){
    setbuf(stdout, NULL);
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    printf("Press Ctrl+C...\n");
    while (1)
        pause();

    return 0;
}
