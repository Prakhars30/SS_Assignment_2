// Catch SIGALRM using the setitimer system call (ITIMER_REAL)

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

#define MSG(s) write(1, s, sizeof(s) - 1)

void handler(int sig){
    MSG("Caught SIGALRM (ITIMER_REAL expired)\n");
}

int main(){
    setbuf(stdout, NULL);
    struct itimerval t;

    signal(SIGALRM, handler);

    t.it_value.tv_sec = 2;
    t.it_value.tv_usec = 0;
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &t, NULL);

    printf("Timer set for 2 seconds\n");
    pause();

    return 0;
}
