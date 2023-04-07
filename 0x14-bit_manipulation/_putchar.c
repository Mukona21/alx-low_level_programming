#include "main.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: 1 if it is a success.
 * On error, return -1 if it is on error, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

