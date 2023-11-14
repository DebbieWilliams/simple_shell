#include "shell.h"

/**
* exit_shell - Terminates the shell with a given exit status
* @inf: Possible arguments in a struct
*
* Return: Specific exit status
*/
int exit_shell(info_t *inf)
{
int exit_check_status;

if (inf->argv[1])
	{
	exit_check_status = _erratoi(inf->argv[1]);
if (exit_check_status == -1)
	{
	inf->status = 2;
	print_error(inf, "Non-numeric value: ");
	_eputs(inf->argv[1]);
	_eputchar('\n');
	return (1);
	}
	inf->err_num = _erratoi(inf->argv[1]);
	return (-2);
	}
	inf->err_num = -1;
	return (-2);
}

/**
* shell_cd - modifies the current directory of the shell process
* @info: Possible arguments in a struct
*
* Return: Always 0
*/
int shell_cd(info_t *info)
{
	char *current_dir, bufsize[1024];
	int dir_change_status;

	current_dir = getcwd(bufsize, 1024);
if (!current_dir)
	_puts("Must handle path retrieval error\n");

if (!info->argv[1])
	{
	dir_change_status = navigate_home(info);
	}
else if (_strcmp(info->argv[1], "-") == 0)
	{
	dir_change_status = navigate_prev(info, current_dir);
	}
else
	{
	dir_change_status = chdir(info->argv[1]);
	}

	if (dir_change_status == -1)
	{
	print_error(info, "unable to navigate to ");
	_eputs(info->argv[1]);
	_putchar('\n');
	}
else
	{
	_setenv(info, "prev_pwd", _getenv(info, "curr_pwd="));
	_setenv(info, "curr_pwd", getcwd(bufsize, 1024));
	}
	return (0);
}

/**
* navigate_home - handles 'cd' command without arguments
* @info: Possible arguments in a struct.
*
* Return: 0 on success, 1 on error
*/
int navigate_home(info_t *info)
{
	char *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
	{
	return (chdir((dir = _getenv(info, "curr_pwd=")) ? dir : "/"));
	}
else
	{
	return (chdir(dir));
	}
}

/**
* navigate_prev - handles 'cd -' shell command
* @info: Possible arguments in a struct.
* @current_dir: The present working directory.
*
* Return: 0 when successful, 1 on failure
*/
int navigate_prev(info_t *info, char *current_dir)
{
	char *dir;

if (!_getenv(info, "prev_pwd="))
	{
	_puts(current_dir);
	_putchar('\n');
	return (1);
	}
	_puts(_getenv(info, "prev_pwd="));
	_putchar('\n');
	dir = _getenv(info, "prev_pwd=");
	return (chdir(dir ? dir : "/"));
}

/**
* shell_help - displays info on built-in shell commands
* @inf: Possible arguments in a struct.
*
* Return: Always 0
*/
int shell_help(info_t *inf)
{
	char **args;

	args = inf->argv;
	_puts("This functionality is not added yet \n");
if (0)
	_puts(*args);
	return (0);
}
