#include "application.h"


int main(int argc, char *argv[]) 
{
    // Check if command-line arguments are provided, otherwise use default file paths
    char *file1 = (argc > 1) ? argv[1] : "../test3/a.txt";
    char *file2 = (argc > 2) ? argv[2] : "../test3/b.txt";

    // Read matrices from files
    Matrix *A = read_matrix(file1);
    Matrix *B = read_matrix(file2);
    if (A->cols != B->rows)
    {
        printf("The number of rows in the first matrix should be equal to the number of columns in the second matrix\n");
        return 1;
    }
    // You should assign 2 matrices values to matrices struct to begin the program 
    // Set the matrices in the global variable
    matrices.matrix1 = A;
    matrices.matrix2 = B;

    // Allocate an empty matrix for storing the result matrix
    Matrix *Matrix_for_save = createMatrix(A->rows, B->cols);
    // Create a thread to multiply the matrices
    pthread_t thread;
    pthread_create(&thread, NULL, multiply_matrix, NULL);
    pthread_join(thread, (void **)&Matrix_for_save);

    // Save the result matrix to a file
    char *saved_matrix_filename_full = "saved_matrices/c_per_matrix.txt";
    write_matrix(saved_matrix_filename_full , Matrix_for_save);
    //free(Matrix_for_save);

    // Allocate an empty matrix for storing the result matrix
    //Matrix_for_save = createMatrix(A->rows, B->cols);

    // Create a thread per row to multiply and store the result
    rowMatrix_stdReturn *returnMatrix;
    for (int i = 0; i < A->rows; i++) 
    {
        pthread_create(&thread, NULL, multiply_row, (void *)(long) i);
        pthread_join(thread, (void**)&returnMatrix);

        for (int j = 0; j < B->cols; j++) 
        {   
            Matrix_for_save->values[returnMatrix->index_row][j] = returnMatrix->matrix->values[0][j];
        }
    }
    
    // Save the result matrix to a file
    char *saved_matrix_filename_rows = "saved_matrices/c_per_row.txt";
    write_matrix(saved_matrix_filename_rows , Matrix_for_save);
    //free(Matrix_for_save);

    // Allocate an empty matrix for storing the result matrix
    //Matrix_for_save = createMatrix(A->rows, B->cols);
    elemantMatrix_stdReturn *returnElemant;

    // Create a thread per element to multiply and store the result
    for (int i = 0; i < A->rows; i++) 
    {
        for (int j = 0; j < B->cols; j++)
        {
            pthread_create(&thread, NULL, multiply_element, (void *)(long)(i * (B -> cols) + j));
            pthread_join(thread, (void **)&returnElemant);
            Matrix_for_save->values[returnElemant->index_row][returnElemant->index_col] = returnElemant->Elemant;
        }
    }

    // Save the result matrix to a file
    char *saved_matrix_filename_elemant = "saved_matrices/c_per_elemant.txt";
    write_matrix(saved_matrix_filename_elemant , Matrix_for_save);
    free(Matrix_for_save);

    return 0;
}
