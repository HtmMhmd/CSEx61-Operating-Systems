#include "readtxt.h"

/**
 * Reads matrix in the format presented in the test cases.
 *
 * @param filename : string (path) which the formatted matrix presents.
 * @return matrix  : struct of type Matrix contains cols, rows, values.
 */
Matrix *read_matrix(char *filename) 
{
    FILE *file = open_txt_File(filename, READ_TXT);
    Matrix *matrix = malloc(sizeof(Matrix));
    store_values_in_txt_into(matrix, file);
    fclose(file);
    return matrix;
}

/**
 * Stores values in the input txt into matrix.
 *
 * @param matrix : pointer to struct of type Matrix (to use dynamic memory allocation).
 * @param file   : pointer to a FILE type (to use dynamic memory allocation).
 */
void store_values_in_txt_into(Matrix *matrix, FILE *file)
{
    int rows_number, columns_number;
    fscanf(file, "row=%d col=%d", &matrix->rows, &matrix->cols);
    rows_number = matrix->rows;
    columns_number = matrix->cols;
    matrix->values = malloc(rows_number * sizeof(int *));

    for (int i = 0; i < matrix->rows; i++) 
    {
        matrix->values[i] = malloc(columns_number * sizeof(int));
        for (int j = 0; j < matrix->cols; j++) 
        {
            fscanf(file, "%d", &matrix->values[i][j]);
        }
    }
}

