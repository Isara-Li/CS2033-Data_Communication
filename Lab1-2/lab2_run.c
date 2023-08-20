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
    char str[15];
    scanf("%s", str);

    int len = strlen(str);
    char *numBuffer = (char *)malloc(len * sizeof(char));

    for (int i = 0; i < len; i++)
    {
        if (str[i] != ' ')
        {
            numBuffer[strlen(numBuffer)] = str[i];
        }
        if (str[i] == ' ' || i == len - 1)
        {
            if (strlen(numBuffer) > 0)
            {
                int num = atoi(numBuffer);
                printf("%d ", num);
                memset(numBuffer, 0, sizeof(numBuffer));
            }
        }
    }

    // Free the memory allocated for the buffer
    free(numBuffer);
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
