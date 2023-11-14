#include "shell.h"

/**
 * present_command_sequence - Presents the command sequence,
 * showing the series of command with numbering starting from 0.
 * @inf: Structure with potential arguments.
 * Return: Always 0
 */
int present_command_sequence(info_t *inf)
{
	print_list(inf->history);
	return (0);
}

/**
 * remove_alias - Erases an alias set for a defined command string.
 * @inf: parameter struct
 * @str: The string to erase the alias for.
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(info_t *inf, char *str)
{
	char *equals_sign, old_char;
	int ret;

	equals_sign = _strchr(str, '=');
if (!equals_sign)
	return (1);

	old_char = *equals_sign;
	*equals_sign = 0;

	ret = delete_node_at_index(&(inf->alias),
	get_node_index(inf->alias, node_starts_with(inf->alias, str, -1)));
	*equals_sign = old_char;

return (ret);
}

/**
 * establish_alias - Assigns an alias for a determined command string.
 * @inf: parameter struct
 * @str: The string to establish an alias for.
 *
 * Return: Always 0 on success, 1 on error
 */
int establish_alias(info_t *inf, char *str)
{
	char *equals_sign;

	equals_sign = _strchr(str, '=');
if (!equals_sign)
	return (1);
if (!*++equals_sign)
	return (remove_alias(inf, str));

	remove_alias(inf, str);
	return (add_node_end(&(inf->alias), str, 0) == NULL);
}

/**
 * output_alias - Outputs the alias string for a given alias node.
 * @node: The alias node to output.
 *
 * Return: Always 0 on success, 1 on error.
 */
int output_alias(list_t *node)
{
	char *equals_sign = NULL, *a = NULL;

if (node)
{
	equals_sign = _strchr(node->str, '=');
for (a = node->str; a <= equals_sign; a++)
	_putchar(*a);
	_putchar('\'');
	_puts(equals_sign + 1);
	_puts("'\n");
	return (0);
}
	return (1);
}

/**
 * _myalias_func - Parallels the functionality of the alias command.
 * Allows users to establish, list, and erase aliases for commands.
 * @inf: Structure containing potential arguments.
 * Return: Always 0
 */
int _myalias_func(info_t *inf)
{
	int i = 0;
	char *equals_sign = NULL;
	list_t *node = NULL;

if (inf->argc == 1)
{
	node = inf->alias;
while (node)
	{
	output_alias(node);
	node = node->next;
	}
	return (0);
}
for (i = 1; inf->argv[i]; i++)
	{
	equals_sign = _strchr(inf->argv[i], '=');
if (equals_sign)
	establish_alias(inf, inf->argv[i]);
else
	output_alias(node_starts_with(inf->alias, inf->argv[i], '='));
	}

	return (0);
}
