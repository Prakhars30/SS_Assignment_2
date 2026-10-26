// Send SIGSTOP to a process using kill. Usage: ./a.out <pid>  (resume it later with: kill -CONT <pid>)

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    if (kill(atoi(argv[1]), SIGSTOP) == -1){
        perror("kill");
        return 1;
    }

    printf("SIGSTOP sent to %s\n", argv[1]);
    return 0;
}
