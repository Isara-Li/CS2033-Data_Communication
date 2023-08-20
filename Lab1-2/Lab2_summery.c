// chain.c implementation
#include <math.h>
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
matrix *create_matrix(int num_rows, int num_cols)
{
    matrix *mat = (matrix *)malloc(sizeof(matrix));
    mat->num_rows = num_rows;
    mat->num_cols = num_cols;
    mat->data = (int **)malloc(num_rows * sizeof(int *));
    for (int i = 0; i < num_rows; ++i)
    {
        mat->data[i] = (int *)calloc(num_cols, sizeof(int));
    }
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

    // Create a copy of the matrix
    matrix *mat_copy = create_matrix(mat->num_rows, mat->num_cols);
    for (int i = 0; i < mat->num_rows; ++i)
    {
        for (int j = 0; j < mat->num_cols; ++j)
        {
            mat_copy->data[i][j] = mat->data[i][j];
        }
    }

    new_node->mat = mat_copy;
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

//-----------------Implementation of Lab1-2-3.c file--------------

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
    node *current = malloc(sizeof(node));
    int num_rows;
    scanf("%d", &num_rows);
    scanf("%*c");
    char input[100];
    fgets(input, sizeof(input), stdin);

    int num_columns = 0;
    int element;
    char *token = strtok(input, " ");
    int row1[100];
    while (token != NULL)
    {

        if (sscanf(token, "%d", &element) == 1)
        {
            num_columns++;
        }
        row1[num_columns - 1] = element;
        token = strtok(NULL, " ");
    }

    matrix *initial_matrix = create_matrix(num_rows, num_columns);
    for (int j = 0; j < num_columns; ++j)
    {
        initial_matrix->data[0][j] = row1[j];
    }

    for (int i = 1; i < num_rows; ++i)
    {
        for (int j = 0; j < num_columns; ++j)
        {
            scanf("%d", &initial_matrix->data[i][j]);
        }
    }

    int index = 0;
    insert_node_after(chn, 0, initial_matrix);
    current = chn->head;
    int function_code = 1;

    while (function_code != 0)
    {
        scanf("%d", &function_code);
        switch (function_code)
        {
        case 2: // add row
            insert_node_after(chn, index, current->mat);
            current = current->next;
            int *row = (int *)malloc(current->mat->num_cols * sizeof(int));
            for (int i = 0; i < current->mat->num_cols; ++i)
            {
                scanf("%d", &row[i]);
            }
            add_row(current->mat, row);
            break;
        case 3: // add col
            insert_node_after(chn, index, current->mat);
            current = current->next;
            int *column = (int *)malloc(current->mat->num_rows * sizeof(int));
            for (int i = 0; i < current->mat->num_rows; ++i)
            {
                scanf("%d", &column[i]);
            }
            add_col(current->mat, column);
            break;
        case 4: // increment
            insert_node_after(chn, index, current->mat);
            current = current->next;
            int num;
            scanf("%d", &num);
            increment(current->mat, num);
            break;
        case 5: // multiply
            insert_node_after(chn, index, current->mat);
            current = current->next;
            int num2;
            scanf("%d", &num2);
            scalar_multiply(current->mat, num2);
            break;
        case 6: // division
            insert_node_after(chn, index, current->mat);
            current = current->next;
            int num3;
            scanf("%d", &num3);
            scalar_divide(current->mat, num3);
            break;
        case 7: // power
            insert_node_after(chn, index, current->mat);
            current = current->next;
            int num4;
            scanf("%d", &num4);
            scalar_power(current->mat, num4);
            break;
        case 8:
            delete_matrix(current->mat);
        case 0:
            break;
        default:
            break;
        }
        index++;
    }
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