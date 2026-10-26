// Print system resource limits using getrlimit

#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

void show(char *name, int res){
    struct rlimit rl;
    getrlimit(res, &rl);

    printf("%-18s soft = ", name);
    if (rl.rlim_cur == RLIM_INFINITY)
        printf("%-20s", "unlimited");
    else
        printf("%-20lu", (unsigned long)rl.rlim_cur);

    printf(" hard = ");
    if (rl.rlim_max == RLIM_INFINITY)
        printf("unlimited\n");
    else
        printf("%lu\n", (unsigned long)rl.rlim_max);
}

int main(){
    show("RLIMIT_CPU", RLIMIT_CPU);
    show("RLIMIT_FSIZE", RLIMIT_FSIZE);
    show("RLIMIT_DATA", RLIMIT_DATA);
    show("RLIMIT_STACK", RLIMIT_STACK);
    show("RLIMIT_CORE", RLIMIT_CORE);
    show("RLIMIT_RSS", RLIMIT_RSS);
    show("RLIMIT_NPROC", RLIMIT_NPROC);
    show("RLIMIT_NOFILE", RLIMIT_NOFILE);
    show("RLIMIT_MEMLOCK", RLIMIT_MEMLOCK);
    show("RLIMIT_AS", RLIMIT_AS);
    show("RLIMIT_LOCKS", RLIMIT_LOCKS);
    show("RLIMIT_SIGPENDING", RLIMIT_SIGPENDING);
    show("RLIMIT_MSGQUEUE", RLIMIT_MSGQUEUE);
    show("RLIMIT_NICE", RLIMIT_NICE);
    show("RLIMIT_RTPRIO", RLIMIT_RTPRIO);
    return 0;
}
