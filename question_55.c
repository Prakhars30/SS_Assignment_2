// Set a system resource limit (maximum open files) using setrlimit

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/resource.h>

int main(){
    struct rlimit rl;

    getrlimit(RLIMIT_NOFILE, &rl);
    printf("Before: soft = %lu, hard = %lu\n", (unsigned long)rl.rlim_cur, (unsigned long)rl.rlim_max);

    rl.rlim_cur = 20;                   // lower the soft limit (cannot exceed the hard limit)
    if (setrlimit(RLIMIT_NOFILE, &rl) == -1){
        perror("setrlimit");
        return 1;
    }

    getrlimit(RLIMIT_NOFILE, &rl);
    printf("After : soft = %lu, hard = %lu\n", (unsigned long)rl.rlim_cur, (unsigned long)rl.rlim_max);

    // verify: open files until open() fails
    int count = 0;
    while (open("/dev/null", O_RDONLY) != -1)
        count++;
    perror("open");
    printf("Opened %d more files before failing (3 descriptors were already in use)\n", count);
    return 0;
}
