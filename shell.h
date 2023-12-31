#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* BUFFER SIZES */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* COMMAND TYPES */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* CONVERSION OPTIONS */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* INPUT METHODS */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* HISTORY-RELATED CONSTANTS */
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

/* ENVIRONMENT VARIABLE */
extern char **environ;

/**
 * struct liststr - singly linked list.
 * @num: the number field.
 * @str: a string
 * @next: points to the next node.
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguments to pass into a function,
 *      allowing a uniform prototype for the function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on, count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buffer: address of pointer to cmd_buffer, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buffer;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
	{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin- Structure that holds information about
 * a built-in command.
 * @type: The string representation of the built-in command.
 * @func: A pointer to the function that implements the built-in command.
 * Description: This structure is used to associate a string that
 * represents a built-in command with the function that
 * implements it.
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
int loophsh(char **);
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char **strtow(char *, char *);
char **strtow2(char *, char);
char *my_memset(char *, int, size_t);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);
int display_command_history(info_t *inf);
int _myalias(info_t *);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
int _cd(info_t *info);
int _cd_home(info_t *info);
int _cd_prev(info_t *info, char *cwd);

/* Include necessary headers */

/* Function declarations */
int exit_shell(info_t *inf);
int shell_cd(info_t *info);
int navigate_home(info_t *info);
int navigate_prev(info_t *info, char *current_dir);
int shell_help(info_t *inf);

/* Add other declarations as needed */

/* Include necessary libraries and define functions used in shell.c*/

int is_delim(char c, char *delimiters);

#include <stddef.h>

/* Your existing structure and necessary includes */

/* Function declarations */

/* env_vars.c */
int display_env_vars(info_t *details);
char *find_env_value(info_t *details, const char *name);
int set_env_variable(info_t *details);
int remove_env_variable(info_t *details);
int fill_env_list(info_t *details);

/* Missing functions declarations */
void display_str_list(list_t *list);
char *match_prefix(const char *str, const char *prefix);
void error_puts(const char *message);
int update_env(info_t *details, const char *name, const char *value);
int unset_environment(info_t *details, const char *name);
void append_node(list_t **head, const char *str);

#include <stddef.h>

/* Your existing structure and necessary includes */

/* Function declarations */

/* ext_string.c */
char *_strncpy(char *dest, const char *src, size_t n);
char *_strncat(char *dest, const char *src, size_t n);
char *_strchr(const char *s, int c);

#endif /* SHELL_H */
