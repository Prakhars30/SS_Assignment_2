// Create three threads and print the ids of the created threads
// Compile: gcc question_58.c -pthread

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

void *thread_fn(void *arg){
    int n = *(int *)arg;
    printf("Thread %d: pthread id = %lu, kernel tid = %ld\n", n, (unsigned long)pthread_self(), syscall(SYS_gettid));
    return NULL;
}

int main(){
    pthread_t t[3];
    int num[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++){
        pthread_create(&t[i], NULL, thread_fn, &num[i]);
        printf("Created thread %d, id = %lu\n", i + 1, (unsigned long)t[i]);
    }

    for (int i = 0; i < 3; i++)
        pthread_join(t[i], NULL);

    printf("Main process pid = %d\n", getpid());
    return 0;
}
