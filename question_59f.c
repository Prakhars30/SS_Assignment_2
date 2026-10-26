// Catch SIGVTALRM using the setitimer system call (ITIMER_VIRTUAL, counts only user mode CPU time)

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

#define MSG(s) write(1, s, sizeof(s) - 1)

void handler(int sig){
    MSG("Caught SIGVTALRM (ITIMER_VIRTUAL expired)\n");
    _exit(0);
}

int main(){
    setbuf(stdout, NULL);
    struct itimerval t;

    signal(SIGVTALRM, handler);

    t.it_value.tv_sec = 2;
    t.it_value.tv_usec = 0;
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_usec = 0;
    setitimer(ITIMER_VIRTUAL, &t, NULL);

    printf("Timer set for 2 seconds of CPU time\n");
    while (1);          // keep the CPU busy so that virtual time advances

    return 0;
}
