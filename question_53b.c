// Interval timer using ITIMER_VIRTUAL for 10 seconds and 10 microseconds
// ITIMER_VIRTUAL counts only the CPU time spent by the process in user mode, so the loop keeps the CPU busy

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

volatile int count = 0;

void handler(int sig){
    count++;
    write(1, "SIGVTALRM expired\n", sizeof("SIGVTALRM expired\n") - 1);
    if (count == 2){
        write(1, "Timer fired twice, exiting\n", sizeof("Timer fired twice, exiting\n") - 1);
        exit(0);
    }
}

int main(){
    struct itimerval t;

    signal(SIGVTALRM, handler);

    t.it_value.tv_sec = 10;
    t.it_value.tv_usec = 10;
    t.it_interval.tv_sec = 10;
    t.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_VIRTUAL, &t, NULL) == -1){
        perror("setitimer");
        return 1;
    }

    while (1);
    return 0;
}
