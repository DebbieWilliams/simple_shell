#include "shell.h"

/**
 * _strncpy - Copies a string with a specified maximum length
 * @dest: The destination string to copy to
 * @src: The source string to copy from
 * @n: The maximum number of characters to copy from src to dest
 *
 * Return: A pointer to the destination string dest.
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	char *ptr = dest;
	size_t i;  /* Declare loop variable here */

	for (i = 0; i < n && *src; i++)
	{
		*dest++ = *src++;
	}

	return (ptr);
}

/**
 * _strncat - Concatenates two strings with a specified maximum length
 * @dest: The destination string to be concatenated with
 * @src: The source string to concatenate to destination
 * @n: The maximum number of bytes from src to be concatenated to dest
 *
 * Return: A pointer to the resulting string destination.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	char *ptr = dest;
	size_t i;  /* Declare loop variable here */

	while (*dest)
	{
		dest++;
	}

	for (i = 0; i < n && *src; i++)
	{
		*dest++ = *src++;
	}

	*dest = '\0';
	return (ptr);
}

/**
 * _strchr - Locate character in a string
 * @s: The string to be searched
 * @c: The character to be located
 *
 * Return:A pointer to the first occurrence of the character c in the string s,
 * or NULL if the character is not found.
 */
char *_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
		{
			return ((char *)s);
		}
		s++;
	}

	return (NULL);
}
