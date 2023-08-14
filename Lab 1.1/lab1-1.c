// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "node.h"

// macros

#define INSERT_BEFORE 1
#define INSERT_AFTER 2
#define DELETE_NODE 3
#define DELETE_LIST 4

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
    insert_node_before(lst, 0, "Sri");
    insert_node_after(lst, 0, "Lanka");
    insert_node_after(lst, -1, "is");
    insert_node_after(lst, -1, "a");
    insert_node_after(lst, -1, "country");
    insert_node_before(lst, 4, "small");
    insert_node_after(lst, -1, "in");
    insert_node_after(lst, -1, "South");
    insert_node_after(lst, -1, "Asia");
    delete_node(lst, 5);
    insert_node_before(lst, 5, "nation");
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
