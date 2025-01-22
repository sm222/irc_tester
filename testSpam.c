

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200
# endif

typedef struct s_info
{
	char	*tmp;
	char	*tmp2;
	char	readtmp[BUFFER_SIZE + 1];
	int		rv;
	size_t	cut;
}	t_info;

void	*ft_sfree(void *p);
void	*ft_calloc(size_t size, size_t count);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
void	ft_bzero(void *p, size_t size);

void	ft_bzero(void *p, size_t size)
{
	if (!p)
		return ;
	while (size--)
		((char *)p)[size] = 0;
}

void	*ft_sfree(void *p)
{
	if (p)
		free(p);
	return (NULL);
}

void	*ft_calloc(size_t size, size_t count)
{
	char	*new;

	new = malloc(size * count);
	if (!new)
		return (new = ft_sfree(new));
	ft_bzero(new, size * count);
	return (new);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *sfree, char *s2)
{
	size_t	s1_i;
	size_t	s2_i;
	char	*new;

	s1_i = ft_strlen(sfree);
	s2_i = ft_strlen(s2);
	new = ft_calloc(s1_i + s2_i + 1, sizeof(char));
	if (!new)
	{
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

char	*ft_tiny_split(char *s, size_t *cut)
{
	char	*new;
	size_t	i;

	i = 0;
	while (s[i])
		if (s[i++] == '\n')
			break ;
	new = ft_calloc(i + 1, sizeof(char));
	if (!new)
		return (new = ft_sfree(new));
	*cut = i;
	while (i--)
		new[i] = s[i];
	return (new);
}

char	ft_find(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\n')
			return ('\n');
		i++;
	}
	return ('0');
}

char	*safe_return(char **book, t_info *t_val)
{
	t_val->tmp = ft_tiny_split(*book, &t_val->cut);
	if (!t_val->tmp)
	{
		*book = ft_sfree(*book);
		return (NULL);
	}
	t_val->tmp2 = *book;
	*book = ft_strjoin(NULL, *book + t_val->cut);
	t_val->tmp2 = ft_sfree(t_val->tmp2);
	return (t_val->tmp);
}

char	*get_next_line(int fd)
{
	static char	*book = NULL;
	t_info		t_val;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (book = ft_sfree(book));
	if (!book)
		book = ft_calloc(1, sizeof(char));
	if (!book)
		return (NULL);
	while (ft_find(book) == '0')
	{
		ft_bzero(t_val.readtmp, BUFFER_SIZE + 1);
		t_val.rv = read(fd, t_val.readtmp, BUFFER_SIZE);
		if (t_val.rv <= 0)
			break ;
		book = ft_strjoin(book, t_val.readtmp);
		if (!book)
			return (NULL);
	}
	if (t_val.rv == -1 || (t_val.rv <= 0 && *book == 0))
	{
		book = ft_sfree(book);
		return (NULL);
	}
	return (safe_return(&book, &t_val));
}





void readFile(const int fd) {
    char* line = "";
    while (line) {
        line = get_next_line(fd);
        if (line && (line[0] != '#' && line[0] != '\n'))
            write(STDOUT_FILENO, line, ft_strlen(line));
        free(line);
        usleep(2000);
    }
    
}

int main(int ac, char** av) {
    if (ac >= 2) {
        int i = 1;
        while (i < ac) {
            int fd = open(av[i], O_RDONLY);
            if (fd < 0) {
                perror("open");
                exit(1);
            }
            readFile(fd);
            close(fd);
            i++;
        }
        char* user = "";
        while (user) {
            user =  get_next_line(0);
            if (user) {
                write(STDOUT_FILENO, user, ft_strlen(user));
                free(user);
            }
        }
    }
}