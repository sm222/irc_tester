#ifndef  _TOOLS_H_
# define _TOOLS_H_

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200
# endif

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

# include <stdio.h>   // for size_t
# include <stdlib.h>  // calloc
# include <unistd.h>  // read
# include <strings.h> // bzero
# include <string.h>

# define  ft_strlen(str)  (!str ? 0 : strlen(str));

typedef struct s_info {
  char*   tmp;
  char*   tmp2;
  char    readtmp[BUFFER_SIZE + 1];
  int     rv;
  size_t  cut;
} t_info;

void*   ft_sfree(void *p);
char*   get_next_line(int fd);
char*   ft_strjoin(char *s1, char *s2);

char*   get_next_line(int fd);
char**  ft_split(char const *s, char c);

#endif