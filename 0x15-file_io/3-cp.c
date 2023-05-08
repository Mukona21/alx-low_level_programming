#include "main.h"
#include <stdio.h>
#include <stdlib.h>

char *create_buffer(char *file);
void close_fd(int fd);

/**
 * create_buffer - Allocates 1024 bytes for a buffer.
 * @file: The name of the file buffer is storing chars for.
 *
 * Return: A pointer to the newly-allocated buffer.
 */
char *create_buffer(char *file)
{
	char *buffer;

	buffer = malloc(sizeof(char) * 1024);

	if (buffer == NULL)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't allocate memory for buffer\n");
		exit(99);
	}

	return (buffer);
}

/**
 * close_fd - Closes a file descriptor.
 * @fd: The file descriptor to be closed.
 */
void close_fd(int fd)
{
	int c;

	c = close(fd);

	if (c == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close file descriptor %d\n", fd);
		exit(100);
	}
}

/**
 * main - Copies the contents of a file to another file.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success.
 *
 * Description: Copies the contents of the file passed as the first argument
 * to the file passed as the second argument. If the argument count is incorrect,
 * the program exits with exit code 97. If file_from does not exist or cannot be
 * read, the program exits with exit code 98. If file_to cannot be created or
 * written to, the program exits with exit code 99. If file_to or file_from
 * cannot be closed, the program exits with exit code 100.
 */
int main(int argc, char *argv[])
{
	int from_fd, to_fd, read_len, write_len;
	char *buffer;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	buffer = create_buffer(argv[2]);
	from_fd = open(argv[1], O_RDONLY);
	read_len = read(from_fd, buffer, 1024);
	to_fd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);

	do {
		if (from_fd == -1 || read_len == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't read from file %s\n", argv[1]);
			free(buffer);
			exit(98);
		}

		write_len = write(to_fd, buffer, read_len);
		if (to_fd == -1 || write_len == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't write to file %s\n", argv[2]);
			free(buffer);
			exit(99);
		}

		read_len = read(from_fd, buffer, 1024);
		to_fd = open(argv[2], O_WRONLY | O_APPEND);

	} while (read_len > 0);

	free(buffer);
	close_fd(from_fd);
	close_fd(to_fd);

	return (0);
}

