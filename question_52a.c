// Concurrent server using fork (one child per client). Use question_51b as the client: ./a.out <ip> 6000

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
    setbuf(stdout, NULL);
    char buf[100], reply[100];
    struct sockaddr_in serv, cli;
    socklen_t len = sizeof(cli);

    signal(SIGCHLD, SIG_IGN);           // do not leave zombie children

    int sd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(6000);

    if (bind(sd, (struct sockaddr *)&serv, sizeof(serv)) == -1){
        perror("bind");
        return 1;
    }
    listen(sd, 5);
    printf("Concurrent (fork) server listening on port 6000...\n");

    while (1){
        int nsd = accept(sd, (struct sockaddr *)&cli, &len);
        if (nsd == -1)
            continue;

        if (fork() == 0){
            close(sd);
            printf("Child %d serving client %s\n", getpid(), inet_ntoa(cli.sin_addr));
            int n = read(nsd, buf, sizeof(buf) - 1);
            buf[n] = '\0';
            printf("Child %d got: %s\n", getpid(), buf);
            sleep(5);                   // simulate work so that clients overlap
            sprintf(reply, "Served by child process %d", getpid());
            write(nsd, reply, strlen(reply));
            close(nsd);
            return 0;
        }
        close(nsd);
    }
    return 0;
}
