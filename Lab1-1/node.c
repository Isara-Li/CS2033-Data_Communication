// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <string.h> // includes strlen(), memcpy()
#include <ctype.h>	// includes toupper(), tolower()

// user-defined header files
#include "node.h" // do not modify this file

// put your function prototypes for additional helper functions below:
node *create_node(char *word)
{
	node *new_node = (node *)malloc(sizeof(node));
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->word = strdup(word);
	return new_node;
}

int get_lenght(list *lst)
{
	node *current = lst->head->next;
	int count = 1;
	while (current != lst->head)
	{
		count++;
		current = current->next;
	}
	return count;
}

// implementation
void insert_node_before(list *lst, int index, char *word)
{
	node *new_node = create_node(word);
	// If the list is empty, the new node becomes the head
	if (lst->head == NULL)
	{
		lst->head = new_node;
		lst->head->next = lst->head;
		lst->head->prev = lst->head; // circular
		return;
	}
	// Find the node at the given index
	node *current = lst->head;
	for (int i = 0; i < abs(index); i++)
	{
		if (index < 0)
		{ // negative index
			current = current->prev;
		}
		else
		{ // positive index
			current = current->next;
		}
	}
	// Insert the new node before the current node
	new_node->prev = current->prev;
	new_node->next = current;
	current->prev->next = new_node;
	current->prev = new_node;

	// If the index was 0, update the head
	if (index == 0)
	{
		lst->head = new_node;
	}
}

void insert_node_after(list *lst, int index, char *word)
{
	if (index < 0)
	{
		index = get_lenght(lst) + index;
	}
	insert_node_before(lst, index + 1, word);
}

char *list_to_sentence(list *lst)
{
	if (lst->head == NULL)
	{
		return NULL; // Return NULL for an empty list
	}

	// Count the total number of characters in the sentence
	int total_length = 0;
	node *current = lst->head;
	do
	{
		total_length += strlen(current->word) + 1; // +1 for space between words
		current = current->next;
	} while (current != lst->head);

	// Allocate memory for the sentence
	char *sentence = (char *)malloc(total_length);
	if (sentence == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}

	// Copy the words from the nodes into the sentence
	sentence[0] = '\0'; // Initialize the sentence as an empty string
	current = lst->head;
	do
	{
		strcat(sentence, current->word);
		strcat(sentence, " "); // Add a space between words
		current = current->next;
	} while (current != lst->head);

	return sentence;
}

void delete_node(list *lst, int index)
{
	// Find the node at the given index
	node *current = lst->head;
	for (int i = 0; i < abs(index); i++)
	{
		if (index < 0)
		{
			current = current->prev;
		}
		else
		{
			current = current->next;
		}
	}

	// Update the next and prev pointers of neighboring nodes
	current->prev->next = current->next;
	current->next->prev = current->prev;

	// If the index was 0 (head), update the head
	if (index == 0)
	{
		lst->head = current->next;
	}

	// Free the memory of the deleted node
	free(current->word);
	free(current);
}

void delete_list(list *lst)
{
	node *current = lst->head;
	do
	{
		node *next = current->next;
		free(current->word);
		free(current);
		current = next;
	} while (current != lst->head);
	lst->head = NULL;
}
