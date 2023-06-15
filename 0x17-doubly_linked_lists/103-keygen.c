#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
 * f23 - gets second or third index of key
 * @username: username
 * @len: length of username
 * @x: sets index to 2 or 3
 * Return: encrypted character
 */
int f23(char *username, int len, int x)
{
	int temp, i = 0, hex;

	if (x == 2)
	{
		temp = 0;
		hex = 0x4f;
		while (i < len)
		{
			temp += username[i];
			i++;
		}
	}
	else
	{
		temp = 1;
		hex = 0x55;
		while (i < len)
		{
			temp *= username[i];
			i++;
		}
	}
	return ((temp ^ hex) & 0x3f);
}


/**
 * f4 - gets fourth index of key
 * @username: username
 * @len: length of username
 * Return: encrypted character
 */
int f4(char *username, int len)
{
	int temp = username[0], i = 0;

	while (i < len)
	{
		if (temp < username[i])
			temp = username[i];
		i++;
	}
	srand(temp ^ 0xe);
	return (rand() & 0x3f);
}


/**
 * f5 - gets fifth index of key
 * @username: username
 * @len: length of username
 * Return: encrypted character
 */
int f5(char *username, int len)
{
	int temp = 0, i = 0;

	while (i < len)
	{
		temp += username[i] * username[i];
		i++;
	}
	return ((temp ^ 0xef) & 0x3f);
}


/**
 * f6 - gets sixth index of key
 * @c: first character of username
 * Return: encrypted character
 */
int f6(char c)
{
	int temp = 0, i = 0;

	while (c > i)
	{
		temp = rand();
		i++;
	}
	return ((temp ^ 0xe5) & 0x3f);
}


/**
 * main - entry point
 * @argc: number of arguments
 * @argv: 2d array of arguments
 * Return: 1 if arguments correct, 0 otherwise
 */
int main(int argc, char **argv)
{
	char password[7];
	char *username = argv[1];
	char key[] =
		"A-CHRDw87lNS0E9B2TibgpnMVys5XzvtOGJcYLU+4mjW6fxqZeF3Qa1rPhdKIouk";
	int len = strlen(username);
	int temp = 0;

	if (argc != 2)
		return (1);

	password[0] = key[(temp = (len ^ 0x3b) & 0x3f)];
	password[1] = key[(temp = f23(username, len, 2))];
	password[2] = key[(temp = f23(username, len, 3))];
	password[3] = key[(temp = f4(username, len))];
	password[4] = key[(temp = f5(username, len))];
	password[5] = key[(temp = f6(username[0]))];
	password[6] = '\0';
	printf("%s", password);
	return (0);
}
