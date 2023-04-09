#include "main.h"
#include <stdio.h>

/**
 * print_binary - print binary representation of a number.
 * @n: The number to be printed in binary.
 * Return: No return.
 */

void print_binary(unsigned long int n)
{
	/*Binary Representation*/
	int b;

	if (n >> 1)
		print_binary(n >> 1);
	_putchar((n & 1) + '0');
}


