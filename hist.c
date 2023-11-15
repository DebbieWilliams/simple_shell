#include "shell.h"

/**
 * construct_hist_filepath - builds the file path for the history file.
 * @inf: Pointer to the info_t structure with environment data.
 *
 * Return: Pointer to the constructed file path. Must be freed by the caller.
 */
char *construct_hist_filepath(info_t *inf)
{
	char *home, *hist_path;

	home = _getenv(inf, "HOME=");

	if (!home)
		return (NULL);

	hist_path = malloc(sizeof(char) * (_strlen(home) + _strlen(HIST_FILE) + 2));

	if (!hist_path)
		return (NULL);

	hist_path[0] = '\0';
	_strncpy(hist_path, home, _strlen(home));
	_strncat(hist_path, "/", 1);
	_strncat(hist_path, HIST_FILE, _strlen(HIST_FILE));

	return (hist_path);
}

/**
 * persist_history - writes the history of commands to a file.
 * @inf: Pointer to the info_t structure with history data.
 *
 * Return: 1 on success, -1 on failure.
 */
int persist_history(info_t *inf)
{
	ssize_t fd;
	char *filename = construct_hist_filepath(inf);
	list_t *node;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return (-1);

	for (node = inf->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}

/**
 * read_history_file - reads history from file
 * @file_descriptor: File descriptor for the history file.
 * @inf: Pointer to the info_t structure with history data.
 *
 * Return: The number of entries in the history list after reading from file.
 */
static int read_history_file(int file_descriptor __attribute__
((unused)), info_t *inf)
{
	(void)inf;  /* Mark the parameter as unused */

	/* Implement the reading logic here */

	return (0);
}
/**
 * read_history - reads history from file
 * @inf: the parameter struct
 * Return: the number of entries in the history list
 * after reading from file.
 */
int read_history(info_t *inf)
{
	int linecount = 0;
	ssize_t file_descriptor;
	char *filename = get_history_file(inf);

	if (!filename)
		return (0);

	file_descriptor = open(filename, O_RDONLY);
	free(filename);

	if (file_descriptor == -1)
		return (0);

	linecount = read_history_file(file_descriptor, inf);

	close(file_descriptor);

	return (linecount);
}

/* Other functions... */

/**
 * reorder_history - Renumbers the history list after modifications.
 * @inf: Pointer to the info_t structure with history data.
 *
 * Return: The count of history entries after reordering.
 */
int reorder_history(info_t *inf)
{
	list_t *node;
	int count;

	for (node = inf->history, count = 0; node; node = node->next, count++)
		node->num = count;

	return (inf->histcount = count);
}
