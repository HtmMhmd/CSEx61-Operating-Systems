#include "writetxt.h"
/**
 * Writes the matrix in the format presented in the test cases to a text file.
 *
 * @param filename - The path of the file where the formatted matrix will be saved.
 * @param matrix - A pointer to the Matrix struct containing the matrix data.
 */
void write_matrix(char *filename, Matrix *matrix) 
{

    // write file
    open_file_t open_type = WRITE_TXT;
    
    // open txt file
    FILE * file = open_txt_File(filename, open_type);
    
    // txt file formatting
    fprintf(file, "row=%d col=%d\n", matrix->rows, matrix->cols);
    
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            fprintf(file, "%d ", matrix->values[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}