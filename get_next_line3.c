#include "utils.c"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

char *get_next_line(int fd)
{	
	static char	*unsaved = NULL;
	char	*unsaved_temp = NULL;
	char	*buffer;
	char	*printable = NULL;
	int	buffer_read;
	int	i_new_line;

	buffer_read = 0;
	i_new_line = 0;
	buffer = malloc(BUFFER_SIZE + 1);
	buffer_read = read(fd, buffer, BUFFER_SIZE);
	buffer[buffer_read] = '\0';

	while (find_new_line(unsaved) == -1 && buffer_read != 0)
	{
		
	}

	return (printable);
}


	int main(void) {
		int fd;
		char *line;
		fd = open("text01.txt", O_RDONLY);
		if (fd == -1) {
			perror("Error opening file");
			return 1;
		}
		while ((line = get_next_line(fd)) != NULL) {
			printf("%s\n", line);
			free(line);
		}
		close(fd);
		return 0;
	}