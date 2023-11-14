#include "shell.h"

/**
 * release_memory - Frees memory allocated to a pointer and sets the pointer
 * to NULL
 * @cleanup_ptr: Pointer to be freed
 *
 * This function releases the memory occupied by the pointer and sets it to
 * NULL. It is used to clean up and free memory that is no longer needed,
 * reducing memory leaks and improving the performance of the system.
 *
 * Return: 1 if the pointer is successfully freed, 0 otherwise.
 */
int release_memory(void **cleanup_ptr)
{
if (cleanup_ptr && *cleanup_ptr)
	{
	free(*cleanup_ptr);
	*cleanup_ptr = NULL;
	return (1);
	}

	return (0);
}
