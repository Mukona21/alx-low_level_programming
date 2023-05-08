#include "main.h"
#include <stdio.h>

int close_file(int fd);
void print_read_error(char *filename);
void print_write_error(char *filename);

/**
 * main - Copies the contents of one file to another.
 * @argc: Number of arguments passed to the program.
 * @argv: Array of arguments passed to the program.
 * Return: Always returns 0, or exits with an error code.
 */
int main(int argc, char *argv[])
{
	ssize_t bytes_read = 1;
	char buffer[1024];
	int fd_from, fd_to;

	/* Check number of arguments */
	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	/* Open and check file_from */
	fd_from = open(argv[1], O_RDONLY);
	if (fd_from < 0)
	{
		print_read_error(argv[1]);
		exit(98);
	}

	/* Open and check file_to */
	fd_to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd_to < 0)
	{
		print_write_error(argv[2]);
		close_file(fd_from);
		exit(99);
	}

	/* Copy contents */
	while (bytes_read)
	{
		/* Read the next 1024 bytes from fd_from and check for read errors */
		bytes_read = read(fd_from, buffer, 1024);
		if (bytes_read < 0)
		{
			print_read_error(argv[1]);
			close_file(fd_from);
			close_file(fd_to);
			exit(98);
		}

		/* Check for end of file */
		if (bytes_read == 0)
			break;

		/* Write the contents to fd_to and check for write errors */
		bytes_read = write(fd_to, buffer, bytes_read);
		if (bytes_read < 0)
		{
			print_write_error(argv[2]);
			close_file(fd_from);
			close_file(fd_to);
			exit(99);
		}
	}

	/* Close files */
	if (close_file(fd_from) < 0)
	{
		close_file(fd_to);
		exit(100);
	}

	if (close_file(fd_to) < 0)
		exit(100);
	return (0);
}

/**
 * close_file - Closes a file descriptor and checks for errors.
 * @fd: File descriptor to be closed.
 * Return: 1 if file descriptor could be closed, -1 if it could not.
 */
int close_file(int fd)
{
	int output;

	output = close(fd);
	if (output < 0)
		dprintf(STDERR_FILENO, "Error: Can't close file descriptor %d\n", fd);
	return (output);
}

/**
 * print_read_error - Prints the read error message.
 * @filename: Name of the file that caused the error.
 */
void print_read_error(char *filename)
{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", filename);
}

/**
 * print_write_error - Prints the write error message.
 * @filename: Name of the file that caused the error.
 */
void print_write_error(char *filename)
{
	dprintf(STDERR_FILENO, "Error: Can't write to file %s\n", filename);
}

