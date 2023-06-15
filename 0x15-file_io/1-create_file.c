#include "main.h"

/**
 * create_file - Creates a file and writes to it.
 * @filename: Name of the file to create.
 * @text_content: String to write to the file.
 *
 * Return: 1 on success, -1 on failure.
 */
int create_file(const char *filename, char *text_content)
{
	int fd, w, len = 0;

	if (filename == NULL)
		return (-1);

	if (text_content != NULL)
	{
		while (text_content[len])
			len++;
	}

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);

	w = write(fd, text_content, len);
	if (w == -1 || (text_content != NULL && w != len))
	{
		close(fd);
		return (-1);
	}

	close(fd);

	return (1);
}