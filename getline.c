#include "shell.h"

/**
* customRead - Function to read input without a newline character.
* @data: Struct containing info.
* @buffer_address: Address of the buffer to store commands.
* @buffer_length: Address of variable where length of buffer is stored.
*
* Return: Returns the number of bytes read from the input.
*/
ssize_t customRead(info_t *data, char **buffer_address, size_t *buffer_length)
{
ssize_t byte_count = 0;
size_t buff_size = 0;

if (!*buffer_length)
{
free(*buffer_address);
*buffer_address = NULL;
signal(SIGINT, customSigintHandler);

#if USE_GETLINE
byte_count = getline(buffer_address, &buff_size, stdin);
#else
byte_count = customGetline(data, buffer_address, &buff_size);
#endif

if (byte_count > 0)
{
if ((*buffer_address)[byte_count - 1] == '\n')
{
(*buffer_address)[byte_count - 1] = '\0';
byte_count--;
}
data->linecount_flag = 1;
remove_comments(*buffer_address);
build_history_list(data, *buffer_address, data->histcount++);
{
*buffer_length = byte_count;
data->cmd_buffer = buffer_address;
}
}
}
return (byte_count);
}

/**
* load_input - Load a line of input from input stream.
* @data: struct with parameters
*
* Return: The number of bytes read.
*/
ssize_t load_input(info_t *data)
{
static char *custom_buffer;
static size_t arr_i, arr_j, arr_len;
ssize_t total_read = 0;
char **buffer_p = &(data->arg);
char *temp_pointer;

_putchar(BUF_FLUSH);
total_read = customRead(data, &custom_buffer, &arr_len);

if (total_read == -1)
return (-1);

if (arr_len)
{
arr_j = arr_i;
temp_pointer = custom_buffer + arr_i;

check_chain(data, custom_buffer, &arr_j, arr_i, arr_len);

while (arr_j < arr_len)
{
if (is_chain(data, custom_buffer, &arr_j))
break;
arr_j++;
}

arr_i = arr_j + 1;

if (arr_i >= arr_len)
{
arr_i = arr_len = 0;
data->cmd_buf_type = CMD_NORM;
}

*buffer_p = temp_pointer;
return (_strlen(temp_pointer));
}

*buffer_p = custom_buffer;
return (total_read);
}

/**
* buffer_read - Function to read a buffer of given size.
* @data: struct containing variable information
* @buffer: Buffer where data will be read into.
* @index: Size of the buffer.
*
* Return: Returns the number of bytes read.
*/
ssize_t buffer_read(info_t *data, char *buffer, size_t *index)
{
ssize_t flag = 0;

if (*index)
return (0);
flag = read(data->readfd, buffer, READ_BUF_SIZE);
if (flag >= 0)
*index = flag;
return (flag);
}

/**
* customGetline - Function to read a line from the input.
* @data: struct containing variable information
* @ptr: Pointer to buffer address, preallocated or NULL.
* @length: Size of the preallocated buffer pointer, if not NULL.
*
* Return: Returns the string read from the input.
*/
int customGetline(info_t
