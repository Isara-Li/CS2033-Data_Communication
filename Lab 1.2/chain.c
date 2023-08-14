#include <stdio.h>
#include <stdlib.h> // includes malloc(), free(), realloc()
#include <string.h> // includes memcpy()

#include "chain.h" // do not modify this file

// put your function prototypes for additional helper functions below:
matrix *allocate_matrix(int num_rows, int num_cols)
{
    matrix *mat = (matrix *)malloc(sizeof(matrix));
    if (mat == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Allocate memory for the data (rows)
    mat->data = (int **)malloc(num_rows * sizeof(int *));
    if (mat->data == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(mat);
        exit(1);
    }

    // Allocate memory for each row (columns) and initialize to zero
    for (int i = 0; i < num_rows; ++i)
    {
        mat->data[i] = (int *)calloc(num_cols, sizeof(int));
        if (mat->data[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            // Clean up already allocated memory
            for (int j = 0; j < i; ++j)
            {
                free(mat->data[j]);
            }
            free(mat->data);
            free(mat);
            exit(1);
        }
    }
    mat->num_rows = num_rows;
    mat->num_cols = num_cols;
    return mat;
}
int power(int base, int exponent)
{
    int result = 1;
    for (int i = 0; i < exponent; ++i)
    {
        result *= base;
    }
    return result;
}

// implementation
matrix *create_matrix(int num_rows, int num_cols)
{
    matrix *mat = allocate_matrix(num_rows, num_cols);
    // All cells in the matrix are already initialized to zero
    return mat;
}

void add_row(matrix *mat, int *row)
{
    if (mat == NULL || row == NULL)
    {
        return;
    }

    // Reallocate memory for the data (rows) to accommodate the new row
    mat->data = (int **)realloc(mat->data, (mat->num_rows + 1) * sizeof(int *));
    if (mat->data == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Allocate memory for the new row (columns) and copy the elements
    mat->data[mat->num_rows] = (int *)malloc(mat->num_cols * sizeof(int));
    if (mat->data[mat->num_rows] == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    memcpy(mat->data[mat->num_rows], row, mat->num_cols * sizeof(int));
    mat->num_rows++;
    free(row); // Caller will free the input row, so we can free it here
}

void add_col(matrix *mat, int *col)
{
    if (mat == NULL || col == NULL)
    {
        return;
    }

    // For each existing row, reallocate memory to add a new column
    for (int i = 0; i < mat->num_rows; ++i)
    {
        mat->data[i] = (int *)realloc(mat->data[i], (mat->num_cols + 1) * sizeof(int));
        if (mat->data[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }

        // Copy the element from the input column to the new column
        mat->data[i][mat->num_cols] = col[i];
    }

    mat->num_cols++;
    free(col); // Caller will free the input col, so we can free it here
}

void increment(matrix *mat, int num)
{
    if (mat == NULL)
    {
        return;
    }

    for (int i = 0; i < mat->num_rows; ++i)
    {
        for (int j = 0; j < mat->num_cols; ++j)
        {
            mat->data[i][j] += num;
        }
    }
}

void scalar_multiply(matrix *mat, int num)
{
    if (mat == NULL)
    {
        return;
    }

    for (int i = 0; i < mat->num_rows; ++i)
    {
        for (int j = 0; j < mat->num_cols; ++j)
        {
            mat->data[i][j] *= num;
        }
    }
}

void scalar_divide(matrix *mat, int num)
{
    if (mat == NULL || num == 0)
    {
        return;
    }

    for (int i = 0; i < mat->num_rows; ++i)
    {
        for (int j = 0; j < mat->num_cols; ++j)
        {
            mat->data[i][j] /= num;
        }
    }
}

void scalar_power(matrix *mat, int num)
{
    if (mat == NULL || num < 0)
    {
        return;
    }

    for (int i = 0; i < mat->num_rows; ++i)
    {
        for (int j = 0; j < mat->num_cols; ++j)
        {
            mat->data[i][j] = power(mat->data[i][j], num);
        }
    }
}

void delete_matrix(matrix *mat)
{
    if (mat == NULL)
    {
        return;
    }

    for (int i = 0; i < mat->num_rows; ++i)
    {
        free(mat->data[i]); // Free memory for each row
    }
    free(mat->data); // Free memory for the data (rows)
    free(mat);       // Free memory for the matrix struct
}

/*
    DO NOT MODIFY BELOW
*/
// print out matrix in row-major order
// elements in the same row are space-separated
// each row starts in a new line
void print_matrix(matrix *mat)
{
    int row_idx, col_idx;
    for (row_idx = 0; row_idx < mat->num_rows; ++row_idx)
    {
        for (col_idx = 0; col_idx < mat->num_cols; ++col_idx)
        {
            if (col_idx == mat->num_cols - 1)
            {
                printf("%d\n", mat->data[row_idx][col_idx]);
            }
            else
            {
                printf("%d ", mat->data[row_idx][col_idx]);
            }
        }
    }
}

// Add the rest of the functions needed for the chain below

node *create_node(matrix *mat)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->mat = mat;
    return new_node;
}

int get_lenght(chain *lst)
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
void insert_node_before(chain *lst, int index, matrix *mat)
{
    node *new_node = create_node(mat);
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

void insert_node_after(chain *lst, int index, matrix *mat)
{
    if (index < 0)
    {
        index = get_lenght(lst) + index;
    }
    insert_node_before(lst, index + 1, mat);
}

void delete_node(chain *lst, int index)
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
    free(current->mat);
    free(current);
}

void delete_list(chain *lst)
{
    node *current = lst->head;
    do
    {
        node *next = current->next;
        free(current->mat);
        free(current);
        current = next;
    } while (current != lst->head);
    lst->head = NULL;
}
