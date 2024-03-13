#include "readtxt.h"

void open_txt_File(char *filename, FILE **file)
{
    /*
    open txt file using filename
    @params
    filename : sring which the formated matrix presents
    file     : double pointer to a FILE type          ( to use dynamic memory allocation)
    */
    *file = fopen(filename, "r");
    if (*file == NULL) 
    {
        printf("Cannot open file %s\n", filename);
        exit(1);
    }
}
void store_values_in_txt_into(Matrix *matrix, FILE **file)
{
    /*
    store values in the input txt into matrix
    @params
    matrix   : pointer to struct of type Matrix ( to use dynamic memory allocation)
    file     : double pointer to a FILE type    ( to use dynamic memory allocation)
    */

    int rows_number, columns_number;
    fscanf(*file, "row=%d col=%d", &matrix->rows, &matrix->cols);
    rows_number     = (matrix->rows);
    columns_number  = (matrix->cols);
    matrix->values = malloc( rows_number * sizeof(int *));

    for (int i = 0; i < matrix->rows; i++) 
    {
        matrix->values[i] = malloc( columns_number * sizeof(int));
        for (int j = 0; j < matrix->cols; j++) 
        {
            fscanf(*file, "%d", &matrix->values[i][j]);
        }
    }
}

Matrix *read_matrix(char *filename) {
    /*
    reads matrix in the format presented in the test cases
    @params
    filename : sring which the formated matrix presents
    @returns 
    matrix   : type struct of cols, rows, values
    */

    // file to store the matrix in stack
    FILE **file = alloca(sizeof(FILE *));
    
    // open txt file
    open_txt_File(filename, file);

    // matrix to store the txt file formated matrix values
    Matrix *matrix = malloc(sizeof(Matrix));
    // store the txt file formated matrix values in matrix refrence
    store_values_in_txt_into(matrix, file);

    fclose(*file);
    return matrix;
}