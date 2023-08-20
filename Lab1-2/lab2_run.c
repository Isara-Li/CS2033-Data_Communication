// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <string.h> // string includes strlen() and memcpy()

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
    int row_num;
    scanf("%d", &row_num);
    int col_num = 4;
    matrix *mat = create_matrix(row_num, col_num);
    for (int i = 0; i < row_num; ++i)
    {
        for (int j = 0; j < col_num; ++j)
        {
            scanf("%d", mat->data[i][j]);
        }
    }
    insert_node_before(chn, 0, mat);
    matrix *mat_1 = create_matrix(mat->num_rows, mat->num_cols);
    // copy the mat in to mat_1'
    memccpy(mat_1, mat, sizeof(mat), sizeof(mat_1));
    while (1)
    {
        int index;
        scanf("%d", &index);
        if (index == 0)
        {
            break;
        }
        if (index == 2)
        {
            int *new_row = (int *)malloc(col_num * sizeof(int));
            for (int i = 0; i < 4; ++i)
            {
                scanf("%d", &new_row[i]);
            }
            add_row(mat_1, new_row);
            insert_node_after(chn, 0, mat_1);
        }
        else if (index == 1)
        {
            int *new_col = (int *)malloc(4 * sizeof(int));
            for (int i = 0; i < 4; ++i)
            {
                scanf("%d", &new_col[i]);
            }
            add_col(mat_1, new_col);
            insert_node_after(chn, 0, mat_1);
        }
        else if (index == 3)
        {
            int row_index;
            scanf("%d", &row_index);
            delete_row(mat_1, row_index);
            insert_node_after(chn, 0, mat_1);
        }
    }
}
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
