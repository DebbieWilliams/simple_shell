#include "shell.h"

/**
* display_env_vars - Outputs the current environment variables.
* @details: Pointer to a struct housing possible arguments.
* Return: 0 to signal success
*/
int display_env_vars(info_t *details)
{
	display_str_list(details->env);
	return (0);
}

/**
* find_env_value - Retrieves the value of a specified environment variable.
* @details: Pointer to a structure with possible arguments.
* @name: The name of the environment variable to search for.
* Return: Pointer to the value, or NULL if not found.
*/
char *find_env_value(info_t *details, const char *name)
{
	list_t *element = details->env;
	char *match;

while (element)
	{
	match = match_prefix(element->str, name);
if (match && *match)
	return (match);
	element = element->next;
	}
	return (NULL);
}

/**
* set_env_variable - Creates or modifies an environment variable.
* @details: Pointer to a structure housing optional arguments.
* Return: 0 on modification or creation, 1 otherwise.
*/
int set_env_variable(info_t *details)
{
if (details->argc != 3)
	{
	error_puts("Invalid number of arguments\n");
	return (1);
	}
if (update_env(details, details->argv[1], details->argv[2]))
	return (0);
	return (1);
}

/**
* remove_env_variable - Removes specified environment variables.
* @details: A structure containing optional arguments.
* Return: 0 on success, -1 on failure.
*/
int remove_env_variable(info_t *details)
{
int index;

if (details->argc < 2)
	{
	error_puts("Insufficient arguments.\n");
	return (-1);
	}

for (index = 1; index < details->argc; index++)
	{
if (!unset_environment(details, details->argv[index]))
	{
	error_puts("Could not remove environment variable.\n");
	return (-1);
	}
	}
	return (0);
}

/**
* fill_env_list - Fills a linked list with current environment variables.
* @details: Structure with optional arguments.
* Return: 0 if successful, -1 on failure.
*/
int fill_env_list(info_t *details)
{
	list_t *element = NULL;
	size_t index;

for (index = 0; environ[index]; index++)
	append_node(&element, environ[index]);
	details->env = element;
	return (0);
}
