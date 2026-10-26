// Ignore SIGINT and then reset it to the default action using the sigaction system call

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(){
    setbuf(stdout, NULL);
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sa.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sa, NULL);
    printf("SIGINT is ignored for 10 seconds, try Ctrl+C (pid %d)\n", getpid());
    sleep(10);

    sa.sa_handler = SIG_DFL;
    sigaction(SIGINT, &sa, NULL);
    printf("SIGINT reset to default action, press Ctrl+C now to terminate\n");
    sleep(10);

    printf("No Ctrl+C received, exiting normally\n");
    return 0;
}
