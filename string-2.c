#include "shell.h"

/**
 * copy_str - Copies a string from source to destination.
 * @dst: Destination buffer.
 * @src: Source string.
 * Return: Pointer to the destination buffer.
 */
char *copy_str(char *dst, const char *src)
{
	int idx = 0;

if (!src || dst == src)
	return (dst);

while (src[idx])
	{
	dst[idx] = src[idx];
	idx++;
	}

	dst[idx] = '\0';

	return (dst);
}

/**
 * create_duplicate - Creates a duplicate of the provided string.
 * @orig: Original string to duplicate.
 * Return: Pointer to duplicated string or NULL if memory allocation fails.
 */
char *create_duplicate(const char *orig)
{
	char *copy;
	int len = 0;

if (!orig)
	return (NULL);

while (orig[len])
	len++;

	copy = (char *)malloc(sizeof(char) * (len + 1));

if (copy == NULL)
	return (NULL);

while (len--)
	copy[len] = orig[len];

	copy[len] = '\0';  /* Add terminating null byte */

	return (copy);
}

/**
 * print_str - Outputs a string to stdout.
 * @str: String to be output.
 */
void print_str(char *str)
{
while (*str)
	{
	print_char(*(str++));
	}
}

/**
 * print_char - Prints a single character to stdout and handles buffer.
 * @c: Character to be printed.
 * Return: 1 on success, -1 on error with errno set accordingly.
 */
int print_char(char c)
{
	static int buff_pos;
	static char buff[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || buff_pos >= WRITE_BUF_SIZE)
	{
	write(1, buff, buff_pos);
	buff_pos = 0;
	}

if (c != BUF_FLUSH)
	buff[buff_pos++] = c;

	return (1);
}
