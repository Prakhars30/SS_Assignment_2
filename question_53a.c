// Interval timer using ITIMER_REAL for 10 seconds and 10 microseconds
// ITIMER_REAL counts real (wall clock) time

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

volatile int count = 0;

void handler(int sig){
    count++;
    write(1, "SIGALRM expired\n", sizeof("SIGALRM expired\n") - 1);
    if (count == 2){
        write(1, "Timer fired twice, exiting\n", sizeof("Timer fired twice, exiting\n") - 1);
        exit(0);
    }
}

int main(){
    struct itimerval t;

    signal(SIGALRM, handler);

    t.it_value.tv_sec = 10;
    t.it_value.tv_usec = 10;
    t.it_interval.tv_sec = 10;
    t.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_REAL, &t, NULL) == -1){
        perror("setitimer");
        return 1;
    }

    while (1)
        pause();
    return 0;
}
