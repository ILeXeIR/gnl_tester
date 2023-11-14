#include "gnl_test.h"

int	check_fails(char const text_in_file[], char *line, int len, int i);

void	print_file_error(int i, int fds[], char *err_msg)
{
	printf("%s\n", err_msg);
	while (i >= 0)
		close(fds[i--]);
}

int	read_files(int fds[], char texts[3][1000], int n)
{
	int		i;
	char	filenames[3][30] = {"files/3_many_lines.txt", "files/5_bonus_lines.txt", "files/6_bonus_lines.txt"};

	i = 0;
	while (i < n)
	{
		fds[i] = open(filenames[i], O_RDONLY);
		if (fds[i] == -1)
		{
			print_file_error(i - 1, fds, "ERROR_IN_TEST: Can't open file.");
			return (1);
		}
		bzero(texts[i], 1000);
		if (read(fds[i], texts[i], 1000) == -1)
		{
			print_file_error(i, fds, "ERROR_IN_TEST: Can't read file.");
			return (1);
		}
		if (lseek(fds[i], 0, SEEK_SET) == -1)
		{
			print_file_error(i, fds, "ERROR_IN_TEST: Can't reset the file position.");
			return (1);
		}
		i++;
	}
	return (0);
}

int	compare_lines_mixed(int fds[], char texts[3][1000], int n)
{
	int		position[] = {0, 0, 0};
	int		counter = 0;
	int		x;
	char	*line;
	int		len;

	while (counter < 30)
	{
		x = (counter++ % 5) % n;
		line = get_next_line(fds[x]);
		if (line == NULL)
		{
			if (texts[x][position[x]] == '\0')
				continue ;
			printf("FAIL Return NULL before end of file: '%s'\n", texts[x] + position[x]);
			return (1);
		}
		len = strlen(line);
		if (check_fails(texts[x], line, len, position[x]) > 0)
		{
			free(line);
			return (1);
		}
		else
			printf(".");
		position[x] += len;
		free(line);
	}
	return (0);
}

void	test_mixed_files(void)
{
	int		fds[3];
	char	texts[3][1000];

	if (read_files(fds, texts, 3) == 1)
		return ;
	if (compare_lines_mixed(fds, texts, 3) == 0)
		printf("\nMultiple files test: OK\n");
	else
		printf("\nMultiple files test: FAIL\n");
	close(fds[0]);
	close(fds[1]);
	close(fds[2]);
}
