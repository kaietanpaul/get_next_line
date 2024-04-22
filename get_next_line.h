#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 40
# endif

int		ft_strlen(const char *str);
int		find_new_line(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *str);
char	*ft_substr(char const *str, unsigned int start, size_t len);

#endif