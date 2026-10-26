// Catch SIGSEGV using the signal system call

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define MSG(s) write(1, s, sizeof(s) - 1)

void handler(int sig){
    MSG("Caught SIGSEGV (segmentation fault)\n");
    _exit(1);           // returning would re-execute the faulting instruction forever
}

int main(){
    signal(SIGSEGV, handler);

    int *p = NULL;
    *p = 10;            // invalid memory access

    return 0;
}
