#include "gnl_test.h"

void	test_mixed_files(void);

int	find_nl(const char *s, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	check_fails(char const text_in_file[], char *line, int len, int i)
{
	if (len == 0)
	{
		printf("FAIL Empty string was returned.\n");
		return (1);
	}
	else if ((line[len - 1] != '\n' && text_in_file[len + i] != '\0')
		|| (strncmp(text_in_file + i, line, len) != 0)
		|| find_nl(text_in_file + i, len - 1) >= 0)
	{
		printf("FAIL Bad line: '%s'\n", line);
		return (1);
	}
	return (0);
}

int	compare_lines(int fd, char const text_in_file[])
{
	int		i;
	char	*line;
	int		len;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		len = strlen(line);
		if (check_fails(text_in_file, line, len, i) > 0)
			break ;
		else
			printf(".");
		i += len;
		free(line);
		line = get_next_line(fd);
	}
	if (line != NULL)
		free(line);
	else if (text_in_file[i] != '\0')
		printf("FAIL Return NULL before end of file: '%s'\n", text_in_file + i);
	else
		return (0);
	return (1);
}

int	test_gnl(char *filename)
{
	int		fd;
	char	text_in_file[1000];

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("ERROR_IN_TEST: Can't open file.\n");
		return (1);
	}
	bzero(text_in_file, 1000);
	if (read(fd, text_in_file, 1000) == -1)
	{
		printf("ERROR_IN_TEST: Can't read file.\n");
		close(fd);
		return (1);
	}
	if (lseek(fd, 0, SEEK_SET) == -1)
	{
		printf("ERROR_IN_TEST: Can't reset the file position.\n");
		close(fd);
		return (1);
	}
	if (compare_lines(fd, text_in_file) == 0)
		printf("\n%s: OK\n", filename + 6);
	else
		printf("\n%s: FAIL\n", filename + 6);
	close(fd);
	return (0);
}

void	test_gnl_0(void)
{
	char	*ptr;

	ptr = get_next_line(9);
	if (ptr != NULL)
	{
		printf("Incorrect fd: FAIL\n");
		free(ptr);
	}
	else
		printf("Incorrect fd: OK\n");
}

int	main(void)
{
	test_gnl_0();
	test_gnl("files/0_empty.txt");
	test_gnl("files/1_only_nl.txt");
	test_gnl("files/2_one_line.txt");
	test_gnl("files/3_many_lines.txt");
	test_gnl("files/4_one_long_line.txt");
	if ((int)TEST_BONUS == 1)
		test_mixed_files();
	return (0);
}
