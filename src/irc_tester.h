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

# define ERRORMSG 10

# define FLAG_LIST "isShvc"

const char* __help[] = {
	"----------------------------------------------",
	"i - give back the control after the scrip run",
	"s - set usleep speed to 100000 (default 1000)",
	"S - set usleep speed to 1000000",
	"v - prits line send from file in stderr",
	"c - like v but add colors to stderr",
	"----------------------------------------------",
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

typedef struct Setting {
	const char*	const	progameName;
	bool				interactive;
	int 				sleep;
	int 				speed;
	int					verbose;
} t_Setting;

#endif