#ifndef  _IRC_TESTER_H_
# define _IRC_TESTER_H_

# include "tools.h"
//
# ifndef COLORS
#  define COLORS
#  define CS  "\001"   //*start code
#  define CE  "\002\0" //*end   code
#  define RED    CS"\e[31m"CE
#  define GRN    CS"\e[32m"CE
#  define YEL    CS"\e[33m"CE
#  define BLU    CS"\e[34m"CE
#  define MAG    CS"\e[35m"CE
#  define CYN    CS"\e[36m"CE
#  define WHT    CS"\e[37m"CE
#  define ORG    CS"\e[38;5;202m"CE
#  define PIK    CS"\e[38;5;176m"CE
#  define TOX    CS"\e[38;5;51m"CE
#  define RESET  CS"\e[0m\022"CE
#  define CLE    CS"\e[1;1H\x1b[2J"CE
#  define GIT    CS"\e[38;5;82m"CE
#  define GIT_B  CS"\e[38;5;94m"CE
#  define MAX_COLORLEN 20
# endif

//
# include <fcntl.h> // open
# include <stdlib.h>
# include <string.h> //strlen
# include <stdbool.h>
//
#include <sys/ioctl.h>
#include <sys/socket.h>

# define ERRORMSG 10

# define FLAG_LIST "isShvchnpf"

# define FORMAT_BUFF 20


static const char* const __flags[] = {
  "interactive",
  "slow",
  "super-slow",
  "verbose",
  "colors",
  "help", //!
  "network",
  "port",
  "format",
  NULL
};

static const char* const __help[] = {
  "i - give back the control after all files are read and send",
  "s - set usleep speed to 100000 (default 1000)",
  "S - set usleep speed to 1000000",
  "v - prits line send from file in stderr",
  "c - like 'v' but add colors to stderr",
  "h - show this message",
  "n - switch to network mode, try to connect on 172.0.0.1 on port 8080",
  "p - like 'n' but you can specify the port value",
  "f - let you switch the end of the line, default :\\r\\n",
  NULL
};

extern const char *Colors[];

typedef struct sockaddr t_sockaddr;

typedef struct args {
  const char** av;
  int*         i;
  size_t*      j;
  size_t*      k;
} t_args;


typedef struct Setting {
  const char* const progameName;
  bool              interactive;
  int               sleep;
  int               speed;
  int               verbose;
  size_t            readBuffer;
  char              format[FORMAT_BUFF];
  t_sockaddr        sock;
  int               fd;
  int               error;
} t_Setting;

void printHelp(void);
void setColors(void);

void SetSetting(t_Setting *sysSetting, int c);
void SetSettingVerbose(t_Setting *sysSetting, const char* const arg);

#endif