// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <string.h>

// user-defined header files
#include "node.h"

// macros

#define INSERT_BEFORE 1
#define INSERT_AFTER 2
#define DELETE_NODE 3
#define DELETE_LIST 4

#define MAX_WORDS 100
// #define MAX_WORD_LENGTH 50

// function prototypes
void print_list(list *lst);
void run(list *lst);

int main()
{
    list *lst = (list *)malloc(sizeof(list));
    lst->head = NULL;
    run(lst);
    print_list(lst);
    free(lst);
    return 0;
}

// parse the input
void run(list *lst)
{
    char input[1000]; // Assuming the input string won't exceed 1000 characters
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int wordCount = 0;

    // Read input string
    printf("Enter a comma-separated string of words: ");
    fgets(input, sizeof(input), stdin);
    input[strlen(input) - 1] = '\0'; // Remove the newline character

    // Tokenize the input string using strtok()
    char *token = strtok(input, ",");
    while (token != NULL && wordCount < MAX_WORDS)
    {
        strcpy(words[wordCount], token);
        wordCount++;
        token = strtok(NULL, ",");
    }
    if (wordCount >= 1)
    {
        insert_node_before(lst, 0, words[0]);
    }
    if (wordCount >= 2)
    {
        insert_node_after(lst, 0, words[1]);
    }
    if (wordCount >= 3)
    {
        for (int i = 2; i < wordCount; i++)
        {
            insert_node_after(lst, -1, words[i]);
        }
    }
    while (1)
    {
        char input[1000]; // Assuming the input string won't exceed 1000 characters
        char words[MAX_WORDS][MAX_WORD_LENGTH];
        int wordCount = 0;

        // Read input string
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0'; // Remove the newline character

        // Tokenize the input string using strtok()
        char *token = strtok(input, " ");
        while (token != NULL && wordCount < MAX_WORDS)
        {
            strcpy(words[wordCount], token);
            wordCount++;
            token = strtok(NULL, " ");
        }

        if (words[0] == '1')
        {
            insert_node_before(lst, words[1], words[2]);
        }
        else if (words[0] == '2')
        {
            insert_node_after(lst, words[1], words[2]);
        }
        else if (words[0] == '3')
        {
            delete_node(lst, words[1]);
        }
        else if (words[0] == '4')
        {
            delete_list(lst);
        }
        else if (words[0] == '0')
        {
            break;
        }
        else
        {
            printf("Invalid input\n");
            break;
        }
    }
}

// Print the list contents
void print_list(list *lst)
{
    node *current = lst->head;
    if (current != NULL)
    {
        printf("%s", current->word);
        current = current->next;
        while (current != lst->head)
        {
            printf(" %s", current->word);
            current = current->next;
        }
    }
    printf("\n");
}
