#include "shell.h"

/**
 * word_count - Count the words in a string by delimiters.
 * @str: The input string.
 * @delimiters: The delimiters character string.
 * Return: Number of words counted or 0 if none.
 */
static int word_count(char *str, char *delimiters)
{
	int count = 0, i = 0;

while (str && str[i])
	{
if (!is_delim(str[i], delimiters) &&
	(is_delim(str[i + 1], delimiters) || str[i + 1] == '\0'))
	count++;
	i++;
	}

	return (count);
}

/**
 * split_string - Separate the strings into words based on delimiters.
 * @str: Input string to split.
 * @delimiters: String containing delimiter characters.
 * Return: Double pointer array containing separated words or NULL on failure.
 */
char **split_string(char *str, char *delimiters)
{
	int word_num, i, j, word_length;
	char **array;

if (str == NULL || *str == '\0' || delimiters == NULL)
	return (NULL);

	word_num = word_count(str, delimiters);
if (word_num == 0)
	return (NULL);

	array = malloc((word_num + 1) * sizeof(char *));
if (array == NULL)
	return (NULL);

for (i = 0, j = 0; j < word_num; j++)
	{
while (is_delim(str[i], delimiters))
	i++;

for (word_length = 0; !is_delim(str[i + word_length],
	delimiters) && str[i + word_length];)
	word_length++;

	array[j] = malloc((word_length + 1) * sizeof(char));
if (array[j] == NULL)
	{
while (j--)
	free(array[j]);

	free(array);
	return (NULL);
	}

	strncpy(array[j], &str[i], word_length);
	array[j][word_length] = '\0';
	i += word_length;
	}

	array[j] = NULL; /* Terminate the array */
	return (array);
}

/**
 * split_string_single_delim - Splits a string using
 * a single character delimiter.
 * @str: The input string to be split.
 * @delimiter: The single character used to split the string.
 * Return: A pointer to an array of strings (words) or NULL if it fails.
 */
char **split_string_single_delim(char *str, char delimiter)
{
	char **words;
	int i, j, length_of_word, words_count;

if (!str || str[0] == '\0')
	return (NULL);

	words_count = word_count(str, &delimiter);
if (words_count == 0)
	return (NULL);

	words = malloc(sizeof(char *) * (words_count + 1));
if (words == NULL)
	return (NULL);

for (i = 0, j = 0; j < words_count; ++j)
	{
while (str[i] == delimiter)
	i++;
for (length_of_word = 0; str[i + length_of_word] &&
	str[i + length_of_word] != delimiter;)
	length_of_word++;

	words[j] = malloc(sizeof(char) * (length_of_word + 1));
if (words[j] == NULL)
	{
while (j--)
	free(words[j]);

	free(words);
	return (NULL);
	}

	memcpy(words[j], &str[i], length_of_word);
	words[j][length_of_word] = '\0';
	i += length_of_word;
	}

	words[j] = NULL; /* Null terminate the list of words */
	return (words);
}
