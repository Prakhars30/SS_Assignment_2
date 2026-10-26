// Create a FIFO file using the mknod system call

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    if (mknod("fifo_mknod_syscall", S_IFIFO | 0666, 0) == -1){
        perror("mknod");
        return 1;
    }
    printf("FIFO created using mknod system call\n");
    return 0;
}
