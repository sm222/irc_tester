#include "tools.h"

void  *ft_sfree(void *p) {
  if (p)
    free(p);
  return (NULL);
}

static size_t  ft_strlen(char *s) {
  size_t  i;

  i = 0;
  while (s && s[i])
    i++;
  return (i);
}

char  *ft_strjoin(char *sfree, char *s2) {
  size_t  s1_i;
  size_t  s2_i;
  char  *new;

  s1_i = ft_strlen(sfree);
  s2_i = ft_strlen(s2);
  new = calloc(s1_i + s2_i + 1, sizeof(char));
  if (!new) {
    sfree = ft_sfree(sfree);
    return (NULL);
  }
  while (s1_i + s2_i-- > s1_i)
    new[s1_i + s2_i] = s2[s2_i];
  while (s1_i--)
    new[s1_i] = sfree[s1_i];
  if (*new == 0)
    new = ft_sfree(new);
  return (ft_sfree(sfree), new);
}

char  *ft_tiny_split(char *s, size_t *cut) {
  char  *new;
  size_t  i;

  i = 0;
  while (s[i])
    if (s[i++] == '\n')
      break ;
  new = calloc(i + 1, sizeof(char));
  if (!new)
    return (new = ft_sfree(new));
  *cut = i;
  while (i--)
    new[i] = s[i];
  return (new);
}

char  ft_find(char *s) {
  size_t  i;

  i = 0;
  while (s && s[i]) {
    if (s[i] == '\n')
      return ('\n');
    i++;
  }
  return ('0');
}

char  *safe_return(char **book, t_info *t_val) {
  t_val->tmp = ft_tiny_split(*book, &t_val->cut);
  if (!t_val->tmp) {
    *book = ft_sfree(*book);
    return (NULL);
  }
  t_val->tmp2 = *book;
  *book = ft_strjoin(NULL, *book + t_val->cut);
  t_val->tmp2 = ft_sfree(t_val->tmp2);
  return (t_val->tmp);
}

char  *get_next_line(int fd) {
  static char  *book = NULL;
  t_info    t_val;

  if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
    return (book = ft_sfree(book));
  if (!book) {
    book = calloc(1, sizeof(char));
    if (!book)
      return (NULL);
  }
  bzero(&t_val, sizeof(t_info));
  while (ft_find(book) == '0') {
    bzero(t_val.readtmp, BUFFER_SIZE + 1);
    t_val.rv = read(fd, t_val.readtmp, BUFFER_SIZE);
    if (t_val.rv <= 0)
      break ;
    book = ft_strjoin(book, t_val.readtmp);
    if (!book)
      return (NULL);
  }
  if (t_val.rv == -1 || (t_val.rv <= 0 && *book == 0)) {
    book = ft_sfree(book);
    return (NULL);
  }
  return (safe_return(&book, &t_val));
}

static void ft_allfree(char **p) {
  int i;

  i = 0;
  while (p[i])
    free(p[i++]);
  free(p);
}

static int  nb_word(const char *str, char c) {
  int i;
  int size;

  i = 0;
  size = 0;
  while (str[i]) {
    while (str[i] && str[i] == c)
      i++;
    if (str[i])
      size++;
    while (str[i] && str[i] != c)
      i++;
  }
  return (size);
}

static char  *ft_strdup_c(const char *str, char c) {
  size_t  i;
  char*   new;

  i = 0;
  while (str[i] && str[i] != c)
    i++;
  new = calloc(i + 1, sizeof(char));
  if (!new)
    return (NULL);
  while (i--)
    new[i] = str[i];
  return (new);
}

/// @brief split a sring on a spesific caracter
/// @param s input 
/// @param c carater
/// @return new double array
char **ft_split(char const *s, char c) {
  char**  new;
  size_t  i;
  size_t  index;

  i = 0;
  index = 0;
  if (!s)
    return (NULL);
  new = calloc(nb_word(s, c) + 1, sizeof(char *));
  if (!new)
    return (NULL);
  while (nb_word(s + i, c)) {
    while (s[i] && s[i] == c)
      i++;
    new[index] = ft_strdup_c(s + i, c);
    if (!new[index++])
      return (ft_allfree(new), NULL);
    while (s[i] && s[i] != c)
      i++;
  }
  return (new);
}