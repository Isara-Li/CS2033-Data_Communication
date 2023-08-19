// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "chain.h"

// function prototypes
void print_chain(chain *chn);
void run(chain *chn);

int main()
{
    chain *chn = (chain *)malloc(sizeof(chain));
    chn->head = NULL;
    run(chn);
    print_chain(chn);
    free(chn);
    return 0;
}

// parse the input
void run(chain *chn)
{
    matrix *mat = create_matrix(3, 4);
    mat->data[0][0] = 1;
    mat->data[0][1] = 1;
    mat->data[0][2] = 2;
    mat->data[0][3] = 5;

    mat->data[1][0] = 2;
    mat->data[1][1] = 5;
    mat->data[1][2] = 4;
    mat->data[1][3] = 7;

    mat->data[2][0] = 3;
    mat->data[2][1] = 1;
    mat->data[2][2] = 4;
    mat->data[2][3] = 7;
    insert_node_before(chn, 0, mat);

    // Create a copy of mat
    matrix *mat_1 = create_matrix(mat->num_rows, mat->num_cols);
    for (int i = 0; i < mat->num_rows; ++i)
    {
        for (int j = 0; j < mat->num_cols; ++j)
        {
            mat_1->data[i][j] = mat->data[i][j];
        }
    }

    int *new_row = (int *)malloc(4 * sizeof(int));
    new_row[0] = 2;
    new_row[1] = 4;
    new_row[2] = 5;
    new_row[3] = 4;
    add_row(mat_1, new_row);
    insert_node_after(chn, 0, mat_1);

    // Create a copy of mat_1
    matrix *mat_2 = create_matrix(mat_1->num_rows, mat_1->num_cols);
    for (int i = 0; i < mat_1->num_rows; ++i)
    {
        for (int j = 0; j < mat_1->num_cols; ++j)
        {
            mat_2->data[i][j] = mat_1->data[i][j];
        }
    }

    increment(mat_2, 1);
    insert_node_after(chn, -1, mat_2);

    // Create a copy of mat_2
    matrix *mat_3 = create_matrix(mat_2->num_rows, mat_2->num_cols);
    for (int i = 0; i < mat_2->num_rows; ++i)
    {
        for (int j = 0; j < mat_2->num_cols; ++j)
        {
            mat_3->data[i][j] = mat_2->data[i][j];
        }
    }

    int *new_col = (int *)malloc(4 * sizeof(int));
    new_col[0] = 3;
    new_col[1] = 4;
    new_col[2] = 7;
    new_col[3] = 2;
    add_col(mat_3, new_col);
    insert_node_after(chn, -1, mat_3);

    // Create a copy of mat_3
    matrix *mat_4 = create_matrix(mat_3->num_rows, mat_3->num_cols);
    for (int i = 0; i < mat_3->num_rows; ++i)
    {
        for (int j = 0; j < mat_3->num_cols; ++j)
        {
            mat_4->data[i][j] = mat_3->data[i][j];
        }
    }

    scalar_power(mat_4, 2);
    insert_node_after(chn, -1, mat_4);
}
// Print the chain
void print_chain(chain *chn)
{
    node *current = chn->head;
    if (current != NULL)
    {

        matrix *mat = current->mat;
        int num_rows = mat->num_rows;
        int num_cols = mat->num_cols;
        for (int i = 0; i < num_rows; ++i)
        {
            for (int j = 0; j < num_cols; ++j)
            {
                printf("%d ", mat->data[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        current = current->next;
        while (current != chn->head)
        {
            matrix *mat = current->mat;
            int num_rows = mat->num_rows;
            int num_cols = mat->num_cols;
            for (int i = 0; i < num_rows; ++i)
            {
                for (int j = 0; j < num_cols; ++j)
                {
                    printf("%d ", mat->data[i][j]);
                }
                printf("\n");
            }
            current = current->next;
            printf("\n");
        }
    }
}
