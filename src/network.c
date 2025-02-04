# include "network.h"

char* getMessage(int fd, size_t buffSize, ssize_t* error) {
  char  buff[buffSize + 1];
  int reseveByte = 0;
  char* rawMessage = NULL;
  bzero(buff, buffSize + 1);
  do {
    rawMessage = ft_strjoin(rawMessage, buff);
    bzero(buff, buffSize + 1);
    ssize_t err = recv(fd, buff, buffSize, MSG_DONTWAIT);
    ioctl(fd, FIONREAD, &reseveByte);
    if (error)
      *error = err;
  }  while (reseveByte > 0);
  return rawMessage;
}


int openSocket(t_sockaddr* sock, int port) {
  static int status = 0;
  if (status == 1)
    return (-1);
  const int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    fprintf(stderr, "socket creation failed\n");
    return -2;
  }
  fprintf(stderr, "socket was create!\n");
  sock->sin_family = AF_INET;
  sock->sin_addr.s_addr = inet_addr("127.0.0.1");
  sock->sin_port = htons(port);
  if (connect(sockfd, (cast_sockaddr*)sock, sizeof(*sock)) != 0) {
    fprintf(stderr, "connection with the server failed: 127.0.0.1:%d\n", port);
    return -2;
  }
  status = 1;
  return sockfd;
}

void connectionClose(int color) {
  if (color > 1)
    fprintf(stderr, "%sconnection was clone with the server%s\n", RED, RESET);
  else
    fprintf(stderr, "connection was clone with the server\n");
}