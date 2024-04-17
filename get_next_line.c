#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

char *get_next_line(int fd)
{
	static int	printed_chars;
	char	*buffer;
	int	i;

	buffer = malloc(sizeof(char) * 10000);
	i = read(fd, buffer, 2000);
	printed_chars += i;
	printf("\n\nprinted chars: %d | ", printed_chars);
	return (buffer);
}

int	main(void)
{
	char	*str;
	int	fd;
	int i = 0;

	fd = open("text00.txt", O_RDONLY);
	while (i <= 10)
	{
		str = get_next_line(fd);
		printf("iteration :%d\n\n%s", i, str);
		i++;
	}
	close(fd);
	return (0);
}