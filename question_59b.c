// Catch SIGINT using the signal system call (press Ctrl+C)

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
    signal(SIGINT, handler);

    printf("Press Ctrl+C...\n");
    while (1)
        pause();

    return 0;
}
