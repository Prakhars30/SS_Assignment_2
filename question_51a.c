// Socket communication between two machines - server (run first, then run question_51b on the other machine)

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
    char buf[100];
    struct sockaddr_in serv, cli;
    socklen_t len = sizeof(cli);

    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1){
        perror("socket");
        return 1;
    }

    int opt = 1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(5555);

    if (bind(sd, (struct sockaddr *)&serv, sizeof(serv)) == -1){
        perror("bind");
        return 1;
    }
    listen(sd, 5);
    printf("Server waiting for a client on port 5555...\n");

    int nsd = accept(sd, (struct sockaddr *)&cli, &len);
    printf("Client connected from %s\n", inet_ntoa(cli.sin_addr));

    int n = read(nsd, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    printf("Message from client: %s\n", buf);

    char *reply = "Hello client, message received by server";
    write(nsd, reply, strlen(reply));

    close(nsd);
    close(sd);
    return 0;
}
