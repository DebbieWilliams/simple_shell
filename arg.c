#include "shell.h"

/**
 * reset_struct_fields - Resets values of an info_t struct fields
 * @inf: An instance of info_t struct
 */
void reset_struct_fields(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * init_struct_fields - Sets the initial values of an info_t struct fields
 * @inf: An instance of info_t struct
 * @argv: Argument vector
 */
void init_struct_fields(info_t *inf, char **argv)
{
	int i;

	inf->fname = argv[0];
if (inf->arg)
	{
	inf->argv = strtow(inf->arg, " \t");
if (!inf->argv)
	{
	inf->argv = malloc(2 * sizeof(char *));
if (inf->argv)
{
	inf->argv[0] = _strdup(inf->arg);
	inf->argv[1] = NULL;
}
	}
for (i = 0; inf->argv && inf->argv[i]; i++)
	{
	/* The body of the loop goes here, if needed */
	}
	inf->argc = i;

	replace_alias(inf);
	replace_vars(inf);
	}
}

/**
 * deallocate_memory_fields - Empties memory occupied by info_t struct fields
 * @inf: An instance of info_t struct
 * @all: Indicator for freeing all fields or selective ones
 */
void deallocate_memory_fields(info_t *inf, int all)
{
	ffree(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
if (all)
	{
if (!inf->cmd_buffer)
	{
	free(inf->arg);
	}
if (inf->env)
	{
	free_list(&(inf->env));
	}
if (inf->history)
	{
	free_list(&(inf->history));
	}
if (inf->alias)
	{
	free_list(&(inf->alias));
	}
	ffree(inf->environ);
	inf->environ = NULL;
	bfree((void **)inf->cmd_buffer);
if (inf->readfd > 2)
	{
	close(inf->readfd);
	}
	_putchar(BUF_FLUSH);
	}
}
