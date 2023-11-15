
#include "shell.h"

/**
 * set_mem - Sets memory with a specific value.
 * @ptr: Pointer to the memory to set.
 * @val: Value to set.
 * @bytes: Number of bytes to set.
 * Return: Pointer to the set memory.
 */
char *set_mem(char *ptr, int val, size_t bytes)
{
	char *start = ptr;

	while (bytes--)
		*ptr++ = (char)val;

	return (start);
}

/**
 * release_memory - Releases memory allocated for a pointer array.
 * @array: The array of pointers to be freed.
 */
void release_memory(char **array)
{
	char **temp = array;

	if (!array)
		return;

	while (*array)
	{
		free(*array);
		array++;
	}

	free(temp);
}

/**
 * resize_memory - Resize a memory block.
 * @old: Pointer to the old memory block.
 * @old_size: Size of the old memory block.
 * @new_size: Size of the new memory block.
 * Return: Pointer to the new memory block.
 */
void *resize_memory(void *old, unsigned int old_size, unsigned int new_size)
{
	char *new_block;

	if (new_size == 0 && old)
	{
		free(old);
		return (NULL);
	}

	if (!old)
		return (malloc(new_size));

	if (new_size == old_size)
		return (old);

	new_block = malloc(new_size);
	if (!new_block)
		return (NULL);

	old_size = (old_size < new_size) ? old_size : new_size;

	while (old_size--)
		new_block[old_size] = ((char *)old)[old_size];

	free(old);
	return (new_block);
}
