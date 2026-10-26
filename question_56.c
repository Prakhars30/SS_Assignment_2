// Measure the time taken to execute 100 getppid() system calls using the time stamp counter (rdtsc)

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

static inline uint64_t read_tsc(){
#if defined(__x86_64__) || defined(__i386__)
    unsigned int lo, hi;
    __asm__ volatile ("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
#else
    uint64_t v;                         // ARM: virtual counter register
    __asm__ volatile ("mrs %0, cntvct_el0" : "=r"(v));
    return v;
#endif
}

int main(){
    uint64_t start = read_tsc();

    for (int i = 0; i < 100; i++)
        getppid();

    uint64_t end = read_tsc();

    printf("Time taken for 100 getppid() calls: %llu cycles\n", (unsigned long long)(end - start));
    printf("Average per call: %llu cycles\n", (unsigned long long)((end - start) / 100));
    return 0;
}
