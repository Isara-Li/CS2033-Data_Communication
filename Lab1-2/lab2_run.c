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
    // printf("%d\n", row_num);
    int col_num = 4;
    matrix *last_matrix = create_matrix(row_num, col_num);
    for (int i = 0; i < row_num; ++i)
    {
        for (int j = 0; j < col_num; ++j)
        {
            scanf("%d", &last_matrix->data[i][j]);
        }
    }

    insert_node_before(chn, 0, last_matrix);

    while (1)
    {
        int func_code;
        scanf("%d", &func_code);
        if (func_code == 0)
        {
            break;
        }
        matrix *new_mat = create_matrix(last_matrix->num_rows, last_matrix->num_cols);
        // Copy the last matrix into new matrix

        for (int i = 0; i < last_matrix->num_rows; ++i)
        {
            for (int j = 0; j < last_matrix->num_cols; ++j)
            {
                new_mat->data[i][j] = last_matrix->data[i][j];
            }
        }

        if (func_code == 2)
        {
            int *new_row = (int *)malloc(4 * sizeof(int));
            for (int i = 0; i < 4; ++i)
            {
                scanf("%d", &new_row[i]);
            }
            add_row(new_mat, new_row);
        }
        else if (func_code == 3)
        {
            int *new_col = (int *)malloc(new_mat->num_rows * sizeof(int));
            for (int i = 0; i < new_mat->num_rows; ++i)
            {
                scanf("%d", &new_col[i]);
            }
            add_col(new_mat, new_col);
        }
        else if (func_code == 4)
        {
            int value;
            scanf("%d", &value);
            increment(new_mat, value);
        }
        else if (func_code == 7)
        {
            int power;
            scanf("%d", &power);
            scalar_power(new_mat, power);
        }

        insert_node_after(chn, -1, new_mat);
        last_matrix = new_mat;
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
