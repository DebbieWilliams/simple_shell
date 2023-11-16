#include "shell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * determine_if_executable - Assess if a pathway points to an executable
 * @pathway: path to assess
 *
 * Return: 1 on being executable, 0 if not
 */
int determine_if_executable(char *pathway)
{
	struct stat buf;

	if (!pathway || access(pathway, X_OK))
		return (0);

	if (!stat(pathway, &buf) && (buf.st_mode & S_IFREG))
		return (1);

	return (0);
}

/**
 * replicate_chars - Copies a subset of characters to a new string
 * @path_env: environment variable PATH
 * @start_idx: starting index within the string
 * @end_idx: ending index within the string
 *
 * Return: pointer to the copy of the subset
 */
char *replicate_chars(char *path_env, int start_idx, int end_idx)
{
	static char tmp_buf[1024];
	int idx, j = 0;

	for (idx = start_idx; idx < end_idx; idx++)
	{
		if (path_env[idx] != ':')
			tmp_buf[j++] = path_env[idx];
	}
	tmp_buf[j] = '\0';
	return (tmp_buf);
}

/**
 * locate_command_path - Identifies the full path of a command using PATH
 * @path_env_var: environment variable PATH
 * @command_name: command to locate
 *
 * Return: the full path if the command is executable or NULL
 */
char *locate_command_path(char *path_env_var, char *command_name)
{
	int i = 0, start = 0;
	char *full_path;

	if (!path_env_var || command_name == NULL)
		return (NULL);

	if (_strlen(command_name) > 2 && starts_with(command_name, "./"))
	{
		if (determine_if_executable(command_name))
			return (command_name);
	}

	while (1)
	{
		if (path_env_var[i] == '\0' || path_env_var[i] == ':')
		{
			full_path = replicate_chars(path_env_var, start, i);
			_strcat(full_path, "/");
			_strcat(full_path, command_name);

			if (determine_if_executable(full_path))
				return (full_path);

			if (path_env_var[i] == '\0')
				break;

			start = ++i;
		}
		else
		{
			i++;
		}
	}
	return (NULL);
}
