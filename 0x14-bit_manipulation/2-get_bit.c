#include "main.h"

/**
 *get_bit - Returns the value of a bit at a given index.
 *@n: number
 *@index: index
 *Return: If an error occurs - -1. Otherwise - The value of bit at index.
 */

int get_bit(unsigned long int n, unsigned int index)
{
	unsigned long int binary, num;

	binary = (sizeof(n) * 8);
	num = -1;

	if (index < binary)
	{
		return (((1 << index) & n) >> index);
	}

	return (num);
}

