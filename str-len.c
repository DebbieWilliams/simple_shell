#include "shell.h"

/**
 * string_length - calculate length of a string
 * @s: string to evaluate
 *
 * Return: the length of the string
 */
int string_length(char *s)
{
	int length = 0;

	if (s == NULL)
		return (0);

	while (s[length])
		length++;

	return (length);
}

/**
 * string_compare - compare two strings
 * @s1: first string to be compared
 * @s2: second string to be compared
 *
 * Return: negative if s1 < s2, 0 if they're equal, positive if s1 > s2
 */
int string_compare(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * string_concatenate - append one string to another
 * @dest: string to append to
 * @src: string to add
 *
 * Return: pointer to the resulting string dest
 */
char *string_concatenate(char *dest, const char *src)
{
	char *dest_end = dest + string_length(dest);

	while (*src)
	{
		*dest_end++ = *src++;
	}

	*dest_end = '\0';

	return (dest);
}

/**
 * string_starts_with - determine if a string starts with another string
 * @str: full string
 * @prefix: string to check if str starts with
 *
 * Return: pointer to the substring or NULL
 */
char *string_starts_with(const char *str, const char *prefix)
{
	while (*prefix)
	{
		if (*prefix++ != *str++)
			return (NULL);
	}

	return ((char *)(str));
}
