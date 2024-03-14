#include "writetxt.h"

void write_matrix(char *filename, Matrix *matrix) 
{
    /*
    writes matrix in the format presented in the test cases
    @params
    filename : sring(path) which the formated matrix will be saved
    @returns 
    matrix   : type struct of cols, rows, values
    */
   
    // file to store the matrix in stack
    FILE **file      = alloca(sizeof(FILE *));
    // write file
    open_file_t open_type = WRITE_TXT;
    // open txt file
    open_txt_File(filename, file, open_type);
    // txt file formatting
    fprintf(*file, "row=%d col=%d\n", matrix->rows, matrix->cols);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            fprintf(*file, "%d ", matrix->values[i][j]);
        }
        fprintf(*file, "\n");
    }

    fclose(*file);
}