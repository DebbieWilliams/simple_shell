#include "shell.h"

/**
 * InteractiveMode - Check if the shell operates interactively
 * @info: Pointer to the infomation structure
 *
 * Return: 1 if in interactive mode, 0 if not
 */
int InteractiveMode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * CheckDelimeter - Evaluates if a character is a delimeter
 * @charToCheck: Character under scrutiny
 * @delimiter: String containing delimeter characters
 *
 * Return: 1 if character is a delimiter, 0 otherwise
 */
int CheckDelimeter(char charToCheck, char *delimiter)
{
while (*delimiter)
if (*delimiter++ == charToCheck)
	return (1);
	return (0);
}

/**
 * IsAlpha - Determines if input is an alphabetic character
 * @ch: Character to be evaluated
 *
 * Return: 1 if alphabetic, 0 if not
 */
int IsAlpha(int ch)
{
if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'))
	return (1);
else
	return (0);
}

/**
 * StringToInteger - Parse string and convert it to integer
 * @str: String to be converted to integer
 *
 * Return: Integer representation of the string
 * or 0 if no numeric characters present
 */
int StringToInteger(char *str)
{
	int index, sign = 1, phase = 0, number;
	unsigned int result = 0;

for (index = 0; str[index] && phase != 2; index++)
	{
if (str[index] == '-')
	sign *= -1;

if (str[index] >= '0' && str[index] <= '9')
	{
	phase = 1;
	result = result * 10 + (str[index] - '0');
	}
else if (phase == 1)
	phase = 2;
	}

	number = (sign == -1) ? -((int)result) : (int)result;

	return (number);
}
