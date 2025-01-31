#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()

#include <sys/ioctl.h>

#define MAX 80
#define PORT 6667

#define SA struct sockaddr

#define ENDL "\r\n"

void func(int sockfd)
{
  char* msg = "PASS abc"ENDL"NICK aaa"ENDL"USER abc * 0 :aaa"ENDL;
  send(sockfd, msg, strlen(msg), 0);
  char buff[10];
  int data = 1;
  while (data) {
    bzero(buff, 10);
    recv(sockfd, buff, 10 - 1, 0);
    ioctl(sockfd, FIONREAD, &data);
    printf("|%i| -> %s\n", data, buff);
  }
}

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        fprintf(stderr, "socket creation failed...\n");
        exit(2);
    }
    fprintf(stderr, "Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        fprintf(stderr, "connection with the server failed...\n");
        exit(2);
    }
    fprintf(stderr, "connected to the server..\n");

    // function for chat
    func(sockfd);
    // close the socket
    close(sockfd);
    return 0;
}