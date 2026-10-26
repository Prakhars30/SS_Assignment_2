// Socket communication between two machines - client
// Usage: ./a.out <server ip> [port]   (default: 127.0.0.1 and 5555)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[]){
    char buf[100];
    struct sockaddr_in serv;
    char *ip = argc > 1 ? argv[1] : "127.0.0.1";
    int port = argc > 2 ? atoi(argv[2]) : 5555;

    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1){
        perror("socket");
        return 1;
    }

    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    inet_pton(AF_INET, ip, &serv.sin_addr);

    if (connect(sd, (struct sockaddr *)&serv, sizeof(serv)) == -1){
        perror("connect");
        return 1;
    }

    char *msg = "Hello server, this is client";
    write(sd, msg, strlen(msg));

    int n = read(sd, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    printf("Message from server: %s\n", buf);

    close(sd);
    return 0;
}
