#include "get_next_line.h"

static char	*add_buffer(char *dest, char *src)
{
	char	*new_str;

	new_str = ft_strjoin(dest, src);
	free(dest);
	return (new_str);
}

static char	*extract_line(char **temp, int i_nl)
{
	char	*line;
	char	*new_temp;

	line = ft_substr(*temp, 0, i_nl + 1);
	new_temp = ft_substr(*temp, i_nl + 1, ft_strlen(*temp) - (i_nl + 1));
	free(*temp);
	*temp = new_temp;
	return (line);
}

static char	*finalize_line(char **temp)
{
	char	*line;

	line = NULL;
	if (*temp && **temp != '\0')
	{
		line = ft_strdup(*temp);
		free(*temp);
		*temp = NULL;
	}
	return (line);
}

static int	read_process_buff(int fd, char **temp, char *buffer, char **line)
{
	int	buff_read;
	int	i_nl;

	i_nl = 0;
	buff_read = read(fd, buffer, BUFFER_SIZE);
	if (buff_read > 0)
	{
		buffer[buff_read] = '\0';
		if (*temp != NULL)
			*temp = add_buffer(*temp, buffer);
		else
			*temp = ft_strdup(buffer);
		i_nl = find_new_line(*temp);
		if (i_nl != -1)
		{
			*line = extract_line(temp, i_nl);
			return (1);
		}
	}
	return (buff_read);
}

char	*get_next_line(int fd)
{
	static char	*temp = NULL;
	char		*line;
	char		*buffer;
	int			buff_read;

	line = NULL;
	buff_read = 0;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (1)
	{
		buff_read = read_process_buff(fd, &temp, buffer, &line);
		if (line != NULL || buff_read <= 0)
			break ;
	}
	if (buff_read == 0 && temp && *temp != '\0')
		line = finalize_line(&temp);
	free(buffer);
	return (line);
}

// int main(int argc, char **argv)
// {
// 	int fd;
// 	char *line;

// 	if (argc > 1)
// 	{
// 		fd = open(argv[1], O_RDONLY);
// 	}
// 	else
// 	{
// 		fd = STDIN_FILENO;
// 	}

// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("Received line: %s", line);
// 		free(line);
// 	}

// 	if (argc > 1)
// 	{
// 		close(fd);
// 	}

// 	return 0;
// }