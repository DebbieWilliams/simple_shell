#include "shell.h"

/**
 * count_list_elements - Counts the number of nodes in a linked list
 * @list: Pointer to the initial node of the linked list
 *
 * Return: The total number of nodes
 */
size_t count_list_elements(const list_t *list)
{
	size_t count = 0;

	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

/**
 * convert_list_to_array - Transforms a linked list to a string array
 * @start: Pointer to the initial node of the list
 *
 * Return: Pointer to the array of strings, or NULL if allocation fails
 */
char **convert_list_to_array(list_t *start)
{
	size_t array_size = count_list_elements(start);
	char **str_array = NULL;
	list_t *temp_node = start;
	size_t i;

	if (!start || array_size == 0)
		return (NULL);

	str_array = malloc((array_size + 1) * sizeof(char *));
	if (!str_array)
		return (NULL);

	for (i = 0; i < array_size; ++i)
	{
		str_array[i] = malloc((_strlen(temp_node->str) + 1) * sizeof(char));
		if (!str_array[i])
		{
			/* Free previously allocated strings if malloc fails */
			while (i > 0)
			{
				free(str_array[--i]);
			}
			free(str_array);
			return (NULL);
		}
		strncpy(str_array[i], temp_node->str, _strlen(temp_node->str));
		/* Fix the third argument */
		temp_node = temp_node->next;
	}
	str_array[array_size] = NULL;
	return (str_array);
}

/**
 * output_list - Prints all elements of a list_t linked list
 * @list: Pointer to the head of the linked list
 * Return: Number of nodes in the list
 */
size_t output_list(const list_t *list)
{
	size_t count = 0;

	while (list)
	{
		_puts(convert_number(list->num, 10, 0));
		/* Assuming FALSE was meant to be 0 */
		_putchar(':');
		_putchar(' ');
		_puts(list->str ? list->str : "(nil)");
		_putchar('\n');
		list = list->next;
		count++;
	}
	return (count);
}

/**
 * find_node_by_prefix - Searches for a node with a string starting with prefix
 * @head: Pointer to the start node of the list
 * @prefix: The prefix string to match against each node's string
 * @next_char: The character following the prefix in the node's string
 *
 * Return: Pointer to the first matching node, or NULL if no match is found
 */
list_t *find_node_by_prefix(list_t *head, char *prefix, char next_char)
{
	char *match = NULL;

	while (head)
	{
		match = starts_with(head->str, prefix);
		if (match && (next_char == -1 || *match == next_char))
			return (head);

		head = head->next;
	}
	return (NULL);
}

/**
 * find_node_index - Retrieves the index of a node in a linked list
 * @initial: Pointer to the start of the list
 * @target: Pointer to the target node within the list
 * Return: Index of the node, or -1 if the node is not found
 */
ssize_t find_node_index(list_t *initial, list_t *target)
{
	size_t index = 0;

	while (initial)
	{
		if (initial == target)
			return ((ssize_t)index);

		initial = initial->next;
		index++;
	}
	return (-1);
}
