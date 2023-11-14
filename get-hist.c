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
	_strcpy(hist_path, home);
	_strcat(hist_path, "/");
	_strcat(hist_path, HIST_FILE);
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
 * read_history - reads history from file
 * @inf: the parameter struct
 * Return: the number of entries in the history list
 * after reading from file.
 */
int read_history(info_t *inf)
{
	int i, last = 0, linecount = 0;
	ssize_t file_descriptor, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history_file(inf);

if (!filename)
	return (0);

	file_descriptor = open(filename, O_RDONLY);
	free(filename);
if (file_descriptor == -1)
	return (0);
if (!fstat(file_descriptor, &st))
	fsize = st.st_size;
if (fsize < 2)
	return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
if (!buffer)
	return (0);
	rdlen = read(file_descriptor, buffer, fsize);
	buffer[fsize] = 0;
if (rdlen <= 0)
	return (free(buffer), 0);
	close(file_descriptor);
for (i = 0; i < fsize; i++)
if (buffer[i] == '\n')
	{
	buffer[i] = 0;
	build_history_list(inf, buffer + last, linecount++);
	last = i + 1;
	}
if (last != i)
	build_history_list(inf, buffer + last, linecount++);
	free(buffer);
	inf->histcount = linecount;
while (inf->histcount-- >= HIST_MAX)
	delete_node_at_index(&(inf->history), 0);
	renumber_history(inf);
	return (inf->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @inf: Structure containing potential arguments. Used to maintain
 * @buffer: the buffer containing the command string
 * to add to the history list.
 * @linecount: the current line number for the command being added.
 *
 * Return: Always 0
 */
int build_history_list(info_t *inf, char *buffer, int linecount)
{
	list_t *new_node = NULL;

if (inf->history)
	new_node = inf->history;
	add_node_end(&new_node, buffer, linecount);

if (!inf->history)
	inf->history = new_node;
	return (0);
}

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
