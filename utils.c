#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = '\0';
	return (ptr);
}

char	*ft_strdup(const char *str)
{
	char	*new_str;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(str) + 1;
	i = 0;
	new_str = malloc(s_len);
	if (new_str)
	{
		while (i < s_len)
		{
			new_str[i] = str[i];
			i++;
		}
	}
	else
		return (NULL);
	return (new_str);
}
char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*new_str;
	size_t	i;
	size_t	make_size;

	i = 0;
	if (!str)
		return (NULL);
	s_len = ft_strlen(str);
	if ((s_len - start) < len)
		make_size = s_len - start;
	else
		make_size = len;
	new_str = (char *)malloc((make_size + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (i < make_size)
	{
		new_str[i] = str[start + i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
int	find_new_line(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}