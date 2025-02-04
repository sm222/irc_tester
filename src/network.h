#ifndef  _NETWORK_H_
# define _NETWORK_H_

# include "tools.h"
# include <sys/socket.h>
# include <netdb.h>
# include <stdio.h>
# include <strings.h> // bzero()
# include <sys/ioctl.h>
# include <arpa/inet.h> // inet_addr()
# include <sys/ioctl.h>

# define MAX  80
# define PORT 6667

# define DEF_ENDL "\r\n"

typedef struct sockaddr_in t_sockaddr;
typedef struct sockaddr    cast_sockaddr;

int   openSocket(t_sockaddr* sock, int port);
char* getMessage(int fd, size_t buffSize, ssize_t* error);
void  connectionClose(int color);
#endif
