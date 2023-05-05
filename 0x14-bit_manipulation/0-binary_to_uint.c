#include "main.h"

/**
 * binary_to_uint - Converts a binary number to an unsigned integer.
 * @b: A pointer to a string of 0 and 1 characters.
 *
 * Return: The converted unsigned integer or 0 if:
 *         - b is NULL.
 *         - There is 1 or more characters in the string b that is not 0 or 1.
 */
unsigned int binary_to_uint(const char *b)
{
	unsigned int converted_num = 0, mult_num = 1;
	int len;

	if (!b)
		return (0);

	for (len = 0; b[len]; len++)
	{
		if (b[len] != '0' && b[len] != '1')
			return (0);
	}

	for (len -= 1; len >= 0; len--)
	{
		converted_num += (b[len] - '0') * mult_num;
		mult_num *= 2;
	}

	return (converted_num);
}

