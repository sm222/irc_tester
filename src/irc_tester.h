#ifndef  _IRC_TESTER_
# define _IRC_TESTER_

# include "tools.h"
//
# ifndef COLORS
#  define COLORS
#  define CS	"\001" //*start code
#  define CE	"\002\0" //*end   code 
#  define RED	CS"\e[31m"CE
#  define GRN	CS"\e[32m"CE
#  define YEL	CS"\e[33m"CE
#  define BLU	CS"\e[34m"CE
#  define MAG	CS"\e[35m"CE
#  define CYN	CS"\e[36m"CE
#  define WHT	CS"\e[37m"CE
#  define ORG	CS"\e[38;5;202m"CE
#  define PIK	CS"\e[38;5;176m"CE
#  define TOX	CS"\e[38;5;51m"CE
#  define RESET	CS"\e[0m\022"CE
#  define CLE	CS"\e[1;1H\x1b[2J"CE
#  define GIT	CS"\e[38;5;82m"CE
#  define GIT_B	CS"\e[38;5;94m"CE
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

# define FLAG_LIST "isShvc"

const char* const __flags[] = {
	"interactive",
	"slow",
	"super-slow",
	"verbose",
	"colors",
	"help",
	NULL
};

const char* const __help[] = {
	"i - give back the control after all files are read and send",
	"s - set usleep speed to 100000 (default 1000)",
	"S - set usleep speed to 1000000",
	"v - prits line send from file in stderr",
	"c - like v but add colors to stderr",
	"h - show this message",
	NULL
};

const char *Colors[] = {
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	NULL
};

typedef struct sockaddr t_sockaddr;

typedef struct Setting {
	const char*	const	progameName;
	bool				interactive;
	int 				sleep;
	int 				speed;
	int					verbose;
	size_t				readBuffer;
	t_sockaddr			sock;
	int					error;
} t_Setting;

#endif