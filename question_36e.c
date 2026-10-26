// Create a FIFO file using the mkfifo library function

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    if (mkfifo("fifo_mkfifo_lib", 0666) == -1){
        perror("mkfifo");
        return 1;
    }
    printf("FIFO created using mkfifo library function\n");
    return 0;
}
