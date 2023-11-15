#include "shell.h"

/**
 * alias_replace - Replaces an alias in the tokenized string
 * with the respective value
 * @inf: pointer to the parameter struct
 * Return: Returns 1 if replacement is successful, 0 otherwise
 */
int alias_replace(info_t *inf)
{
	int i;
	list_t *node;
	char *alias_position;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		alias_position = _strchr(node->str, '=');
		if (!alias_position)
			return (0);
		alias_position = _strdup(alias_position + 1);
		if (!alias_position)
			return (0);
		inf->argv[0] = alias_position;
	}
	return (1);
}

/**
 * vars_replace - Replaces environment variables in the tokenized string
 * @inf: pointer to the parameters struct
 * Return: 1 if replacement is successful, 0 otherwise
 */
int vars_replace(info_t *inf)
{
	int i = 0;
	list_t *node;

	for (i = 0; inf->argv[i]; i++)
	{
		if (inf->argv[i][0] != '$' || !inf->argv[i][1])
			continue;
		if (!_strcmp(inf->argv[i], "$?"))
		{
			replace_string(&(inf->argv[i]), _strdup(convert_number
			(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[i], "$$"))
		{
			replace_string(&(inf->argv[i]), _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(inf->env, &inf->argv[i][1], '=');
		if (node)
		{
			replace_string(&(inf->argv[i]), _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&inf->argv[i], _strdup(""));
	}
	return (1);
}

/**
 * replace_string - Modifies the contents of an old string
 * with the current string
 * @prev: address of pointer to the previous string
 * @current: pointer to the new string
 * Return: Returns 1 if replacement is successful, 0 otherwise
 */
int replace_string(char **prev, char *current)
{
	free(*prev);
	*prev = current;
	return (1);
}

/**
 * find_chain - Checks for a command chain delimiter in the current character
 * @inf: the parameter struct
 * @buffer: the character buffer
 * @pos: Current position in buffer's address
 * Return: Returns 1 if character is command chain delimiter,
 * 0 if not
 */
int find_chain(info_t *inf, char *buffer, size_t *pos)
{
	size_t currentIndex = *pos;

	if (buffer[currentIndex] == '|' && buffer[currentIndex + 1] == '|')
	{
		buffer[currentIndex] = 0;
		currentIndex++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buffer[currentIndex] == '&' && buffer[currentIndex + 1] == '&')
	{
		buffer[currentIndex] = 0;
		currentIndex++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buffer[currentIndex] == ';')
	{
		buffer[currentIndex] = 0;
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = currentIndex;
	return (1);
}

/**
 * chain_verify - Validates if command chaining should
 * proceed based on the recent status
 * @inf: Parameters struct
 * @buffer: Buffer's pointer
 * @pos: Position in the buffer's address
 * @i: Initial buffer position
 * @len: Buffer's length
 * Return: No returns
 */
void chain_verify(info_t *inf, char *buffer, size_t *pos, size_t i, size_t len)
{
	size_t currentIndex = *pos;

	if (inf->cmd_buf_type == CMD_AND && inf->status)
	{
		buffer[i] = 0;
		currentIndex = len;
	}
	if (inf->cmd_buf_type == CMD_OR && !inf->status)
	{
		buffer[i] = 0;
		currentIndex = len;
	}
	*pos = currentIndex;
}
