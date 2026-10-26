// Concurrent server using pthread_create (one thread per client). Use question_51b as the client: ./a.out <ip> 6001
// Compile: gcc question_52b.c -pthread

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void *serve(void *arg){
    int nsd = *(int *)arg;
    free(arg);
    char buf[100], reply[100];

    int n = read(nsd, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    printf("Thread %lu got: %s\n", (unsigned long)pthread_self(), buf);
    sleep(5);                           // simulate work so that clients overlap
    sprintf(reply, "Served by thread %lu", (unsigned long)pthread_self());
    write(nsd, reply, strlen(reply));
    close(nsd);
    return NULL;
}

int main(){
    setbuf(stdout, NULL);
    struct sockaddr_in serv, cli;
    socklen_t len = sizeof(cli);

    int sd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(6001);

    if (bind(sd, (struct sockaddr *)&serv, sizeof(serv)) == -1){
        perror("bind");
        return 1;
    }
    listen(sd, 5);
    printf("Concurrent (pthread) server listening on port 6001...\n");

    while (1){
        int *nsd = malloc(sizeof(int));
        *nsd = accept(sd, (struct sockaddr *)&cli, &len);
        if (*nsd == -1){
            free(nsd);
            continue;
        }
        pthread_t tid;
        pthread_create(&tid, NULL, serve, nsd);
        pthread_detach(tid);
    }
    return 0;
}
