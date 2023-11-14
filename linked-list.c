#include "shell.h"

/**
* prepend_node - Inserts a node at the start of a list
* @top: Double pointer to the first node
* @value: The value to store in the new node
* @length: The length of the string held by the node
*
* Return: A pointer to the new node or NULL if it fails
*/
list_t *prepend_node(list_t **top, const char *value, int length)
{
	list_t *new_node;

if (!top)
	return (NULL);

	new_node = malloc(sizeof(list_t));
if (!new_node)
	return (NULL);

	clear_memory((void *)new_node, 0, sizeof(list_t));
	new_node->num = length;

if (value)
	{
	new_node->str = duplicate_string(value);
if (!new_node->str)
	{
	free(new_node);
	return (NULL);
	}
	}

	new_node->next = *top;
	*top = new_node;

	return (new_node);
}

/**
* append_node - Attaches a new node at the end of the list
*
* @top: The head of the list to which we'll append a new node
* @value: The string associated with the new node
* @length: The index for the node
*
* Return: The newly appended node or NULL if it fails
*/
list_t *append_node(list_t **top, const char *value, int length)
{
	list_t *new_end;
	list_t *current;
if (!top)
	return (NULL);

	new_end = malloc(sizeof(list_t));
if (!new_end)
	return (NULL);

	clear_memory((void *)new_end, 0, sizeof(list_t));
	new_end->num = length;

if (value)
	{
	new_end->str = duplicate_string(value);
if (!new_end->str)
	{
	free(new_end);
	return (NULL);
	}
	}
if (*top)
	{
	current = *top;
while (current->next)
	current = current->next;
	current->next = new_end;
	}
else
	{
	*top = new_end;
	}

	return (new_end);
}

/**
 * display_list_strings - Prints the 'str' element of all nodes in the list
 * @node: The start node
 * Return: The number of nodes
 */
size_t display_list_strings(const list_t *node)
{
	size_t count = 0;

while (node)
	{
	output(node->str ? node->str : "(nil)");
	output("\n");
	node = node->next;
	count++;
	}
	return (count);
}

/**
 * remove_node_by_index - Eliminates a specific node determined by its index
 * @top: Pointer to the list's head
 * @idx: The index at which to remove the node
 * Return: 1 if succeeded, 0 on failure
 */
int remove_node_by_index(list_t **top, unsigned int idx)
{
	list_t *current_node, *node_prior;
	unsigned int counter = 0;

if (!top || !*top)
	return (0);
	current_node = *top;
if (idx == 0)
	{
	*top = current_node->next;
	free(current_node->str);
	free(current_node);
	return (1);
	}
while (current_node)
	{
if (counter == idx)
	{
	node_prior->next = current_node->next;
	free(current_node->str);
	free(current_node);
	return (1);
	}
	node_prior = current_node;
	current_node = current_node->next;
	counter++;
	}
	return (0);
}

/**
 * destroy_list - Clears out all nodes in the list and frees memory
 * @head_ptr: The address to the head of the list
 * Return: None
 */
void destroy_list(list_t **head_ptr)
{
	list_t *current, *next;

if (!head_ptr || !*head_ptr)
	return;
	current = *head_ptr;

while (current)
	{
	next = current->next;
	free(current->str);
	free(current);
	current = next;
	}
	*head_ptr = NULL;
}
