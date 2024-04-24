/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpaul <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:13:29 by kpaul             #+#    #+#             */
/*   Updated: 2024/04/24 21:13:32 by kpaul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

	i_nl = find_new_line(*temp);
	if (*temp && i_nl > -1)
	{
		*line = extract_line(temp, i_nl);
		return (1);
	}
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
	static char	*temps[MAX_FD] = {NULL};
	char		*line;
	char		*buffer;
	int			buff_read;

	line = NULL;
	buff_read = 0;
	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= MAX_FD)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (1)
	{
		buff_read = read_process_buff(fd, &temps[fd], buffer, &line);
		if (line != NULL || buff_read <= 0)
			break ;
	}
	if (buff_read == 0 && temps[fd] && *temps[fd] != '\0')
		line = finalize_line(&temps[fd]);
	free(buffer);
	return (line);
}

// int	main(void)
// {
// 	int fd0, fd1, fd2;
// 	char *line0, *line1, *line2;
// 	fd0 = open("text00.txt", O_RDONLY);
// 	fd1 = open("text01.txt", O_RDONLY);
// 	fd2 = open("text02.txt", O_RDONLY);
// 	if (fd0 == -1 || fd1 == -1 || fd2 == -1) {
// 		printf("Error\n");
// 		return 1;
// 	}
// 	printf("Read:\n");
// 	do
// 	{
// 		line0 = get_next_line(fd0);
// 		line1 = get_next_line(fd1);
// 		line2 = get_next_line(fd2);
// 		if (line0)
// 		{
// 			printf("FD0: %s", line0);
// 			free(line0);
// 		}
// 		if (line1)
// 		{
// 			printf("FD1: %s", line1);
// 			free(line1);
// 		}
// 		if (line2)
// 		{
// 			printf("FD2: %s", line2);
// 			free(line2);
// 		}
// 	}
// 		while (line0 || line1 || line2);
// 	close(fd0);
// 	close(fd1);
// 	close(fd2);
// 	return 0;
// }
