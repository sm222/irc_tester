#ifndef  _IRC_TESTER_H_
# define _IRC_TESTER_H_

# include "tools.h"
# include "network.h"
//


//
# include <fcntl.h> // open
# include <stdlib.h>
# include <string.h> //strlen
# include <stdbool.h>
//


# define ERRORMSG 10

# define FLAG_LIST "isShvchnpf"

# define FORMAT_BUFF_SIZE 20


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

typedef struct args {
  const char* const* av;
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
  char              format[FORMAT_BUFF_SIZE];
  t_sockaddr        sock;
  int               port;
  int               fd;
  int               error;
  t_args            args;
} t_Setting;

void printHelp(void);
void setColors(void);

void SetSetting(t_Setting *sysSetting);
void SetSettingVerbose(t_Setting *sysSetting, const char* const arg);

#endif