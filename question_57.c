// Print system limitations using sysconf

#include <stdio.h>
#include <unistd.h>

int main(){
    printf("Maximum length of arguments for exec family   : %ld\n", sysconf(_SC_ARG_MAX));
    printf("Maximum simultaneous processes per user id    : %ld\n", sysconf(_SC_CHILD_MAX));
    printf("Number of clock ticks (jiffies) per second    : %ld\n", sysconf(_SC_CLK_TCK));
    printf("Maximum number of open files                  : %ld\n", sysconf(_SC_OPEN_MAX));
    printf("Size of a page                                : %ld bytes\n", sysconf(_SC_PAGESIZE));
    printf("Total number of pages in physical memory      : %ld\n", sysconf(_SC_PHYS_PAGES));
    printf("Number of currently available pages in memory : %ld\n", sysconf(_SC_AVPHYS_PAGES));
    return 0;
}
