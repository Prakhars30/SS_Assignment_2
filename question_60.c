// Ignore SIGINT and then reset it to the default action using the signal system call

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(){
    setbuf(stdout, NULL);
    signal(SIGINT, SIG_IGN);
    printf("SIGINT is ignored for 10 seconds, try Ctrl+C (pid %d)\n", getpid());
    sleep(10);

    signal(SIGINT, SIG_DFL);
    printf("SIGINT reset to default action, press Ctrl+C now to terminate\n");
    sleep(10);

    printf("No Ctrl+C received, exiting normally\n");
    return 0;
}
