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
        // print_list(lst);
    }
    if (wordCount >= 2)
    {
        insert_node_after(lst, 0, words[1]);
        // print_list(lst);
    }
    if (wordCount >= 3)
    {
        for (int i = 2; i < wordCount; i++)
        {
            insert_node_after(lst, -1, words[i]);
            // print_list(lst);
        }
    }
    while (1)
    {
        int choice;
        scanf("%d", &choice);
        if (choice == 0)
        {
            break;
        }
        else if (choice == INSERT_BEFORE)
        {
            // print_list(lst);
            int index;
            char word_0[MAX_WORD_LENGTH];
            scanf("%d %s", &index, word_0);
            insert_node_before(lst, index, word_0);
            // print_list(lst);
        }
        else if (choice == INSERT_AFTER)
        {
            // print_list(lst);
            int index;
            char word_1[MAX_WORD_LENGTH];
            scanf("%d %s", &index, word_1);
            insert_node_after(lst, index, word_1);
            // print_list(lst);
        }
        else if (choice == DELETE_NODE)
        {
            int index;
            scanf("%d", &index);
            delete_node(lst, index);
        }
        else if (choice == DELETE_LIST)
        {
            delete_list(lst);
        }
        else
        {
            printf("Invalid choice!\n");
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
