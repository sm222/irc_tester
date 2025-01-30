#ifndef  _TOOLS_H_
# define _TOOLS_H_

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200
# endif

# include <stdio.h>   // for size_t
# include <stdlib.h>  // calloc
# include <unistd.h>  // read
# include <strings.h> // bzero


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