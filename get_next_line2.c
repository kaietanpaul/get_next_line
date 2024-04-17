#include "utils.c"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 20
#endif

char *get_next_line(int fd)
{
	static char	*unsaved = NULL;
	char	*unsaved_temp;
	char	*buffer;
	char	*printable = NULL;
	int	buffer_read;
	int	i_new_line;

	buffer_read = 0;
	i_new_line = 0;
	buffer = malloc(BUFFER_SIZE);
	buffer_read = read(fd, buffer, BUFFER_SIZE);

	if (buffer_read > 0)
	{
		if (unsaved)
		{
			unsaved_temp = ft_strjoin(unsaved, buffer);
			free(unsaved);
			unsaved = ft_strjoin(unsaved_temp, buffer);
			free(unsaved_temp);
		}
		else
			unsaved = ft_strdup(buffer);
	
		i_new_line = find_new_line(unsaved);
		if (i_new_line > -1)
		{
			printable = ft_substr(unsaved, 0, i_new_line);
			free(unsaved);
			unsaved = ft_substr(buffer, i_new_line, ft_strlen(buffer));
		}
	}
	free(buffer);
	return (printable);
}

int	main(void)
{
	char	*str;
	int	fd;
	int i = 0;

	fd = open("text01.txt", O_RDONLY);
	while (i <= 50)
	{
		str = get_next_line(fd);
		if (str)
			printf("iteration :%d\n%s\n", i, str);
		else
			printf("\niteration :%d ------------------\n", i);
		i++;
		free(str);
	}
	close(fd);
	return (0);
}