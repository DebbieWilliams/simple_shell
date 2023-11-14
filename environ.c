#include "shell.h"

/**
* generate_environment_copy - Generates duplicate of existing environment
* @primary_info: Pointer to structure containing arguments
*
* Return: Pointer to copy of environment if successful, else NULL
*/
char **generate_environment_copy(info_t *primary_info)
{
if (!primary_info->environ || primary_info->env_changed)
	{
	primary_info->environ = list_to_strings(primary_info->env);
	primary_info->env_changed = 0;
	}

	return (primary_info->environ);
}

/**
* remove_env_var - Erases an environment variable from the list
* @primary_info: Pointer to structure containing potential arguments
* @environment_var: Name of environmental variable to be removed
*
* Return: 1 if the variable was successfully removed, otherwise 0
*/
int remove_env_var(info_t *primary_info, char *environment_var)
{
	list_t *temp_node = primary_info->env;
	size_t idx_tracker = 0;
	char *temp_ptr;

if (!temp_node || !environment_var)
	return (0);

while (temp_node)
	{
	temp_ptr = starts_with(temp_node->str, environment_var);
if (temp_ptr && *temp_ptr == '=')
	{
	primary_info->env_changed = delete_node_at_index(
	&(primary_info->env),
	idx_tracker
);
	idx_tracker = 0;
	temp_node = primary_info->env;
	continue;
	}
	temp_node = temp_node->next;
	idx_tracker++;
	}

	return (primary_info->env_changed);
}

/**
* update_environment_var - Updates or sets the value of an environment variable
* @primary_info: Pointer to structure with potential arguments
* @environment_var: Environment variable to be updated or set
* @new_value: New value to be assigned to the environment variable
*
* Return: Always returns 0
*/
int update_environment_var(
	info_t *primary_info,
	char *environment_var,
	char *new_value
);
{
	list_t *temp_node;
	char *buf = NULL;
	char *temp_ptr;

if (!environment_var || !new_value)
	return (0);

	buf = malloc(_strlen(environment_var) + _strlen(new_value) + 2);
if (!buf)
	return (1);

	_strcpy(buf, environment_var);
	_strcat(buf, "=");
	_strcat(buf, new_value);

	temp_node = primary_info->env;
while (temp_node)
	{
	temp_ptr = starts_with(temp_node->str, environment_var);
if (temp_ptr && *temp_ptr == '=')
	{
	free(temp_node->str);
	temp_node->str = buf;
	primary_info->env_changed = 1;
	return (0);
	}
	temp_node = temp_node->next;
	}

	add_node_end(&(primary_info->env), buf, 0);
	primary_info->env_changed = 1;

	return (0);
}
