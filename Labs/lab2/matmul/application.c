#include "application.h"

// global as it's used for read-only access
MatrixStacked matrices;


int main(int argc, char *argv[]) 
{
    // Check if command-line arguments are provided, otherwise use default file paths
    char *file1 = (argc > 1) ? argv[1] : "../test1/a.txt";
    char *file2 = (argc > 2) ? argv[2] : "../test1/b.txt";

    // Read matrices from files
    Matrix *A = read_matrix(file1);
    Matrix *B = read_matrix(file2);

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
    free(Matrix_for_save);

    // Allocate an empty matrix for storing the result matrix
    Matrix_for_save = createMatrix(A->rows, B->cols);

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
    free(Matrix_for_save);

    // Allocate an empty matrix for storing the result matrix
    Matrix_for_save = createMatrix(A->rows, B->cols);
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

/**
 * Function: multiply_matrix
 * -------------------------
 * Multiplies two matrices and stores the result in a new matrix.
 *
 * @param arg: Unused argument (required for thread function signature).
 *
 * @return: A pointer to a struct containing the result matrix .
 */
void *multiply_matrix(void *arg) {
    Matrix* A = matrices.matrix1;
    Matrix* B = matrices.matrix2;

    // Allocate memory for the result matrix
    Matrix *C = createMatrix(A->rows, B->cols);

    // Multiply matrices A and B
    for (int i = 0; i < C->rows; i++) 
    {
        for (int j = 0; j < C->cols; j++) 
        {
            C->values[i][j] = multiply_row_col(A, B, i, j);
        }
    }
    return C;
}

/**
 * Function: multiply_row
 * ----------------------
 * Multiplies a row of matrix A with matrix B and stores the result in a new matrix.
 *
 * @param arg: The row index to multiply.
 *
 * @return: A pointer to a struct containing the result matrix and its data.
 */
void *multiply_row(void *arg) {
    int row = (long)arg;

    // Allocate memory for the result matrix
    rowMatrix_stdReturn *returnMatrix = malloc(sizeof(rowMatrix_stdReturn));
    Matrix* A = matrices.matrix1;
    Matrix* B = matrices.matrix2;
    Matrix *C = createMatrix(1, B->cols);

    // Multiply row of A with matrix B
    for (int j = 0; j < C->cols; j++) 
    {
        C->values[0][j] = multiply_row_col(A, B, row, j);
    }

    // Set the data of the result matrix
    returnMatrix->index_col = C->cols;
    returnMatrix->index_row = row;
    returnMatrix->matrix = C;

    return returnMatrix;
}

/**
 * Function: multiply_element
 * --------------------------
 * Multiplies an element of matrix A with matrix B and stores the result.
 *
 * @param arg: The index of the element to multiply.
 *
 * @return: A pointer to a struct containing the result element and its metadata.
 */
void *multiply_element(void *arg) {
    elemantMatrix_stdReturn* returnElemant = malloc(sizeof(elemantMatrix_stdReturn));
    Matrix* A = matrices.matrix1;
    Matrix* B = matrices.matrix2;

    int row = (long)arg / (B->cols);
    int col = (long)arg % (B->cols);

    // Multiply element of A with element of B
    int value = multiply_row_col(A, B, row, col);
    
    // Set the metadata of the result element
    returnElemant->index_row = row;
    returnElemant->index_col = col;
    returnElemant->Elemant = value;
    return returnElemant;
}

/**
 * Function: multiply_row_col
 * --------------------------
 * Multiplies a row of matrix A with a column of matrix B and returns the result.
 *
 * @param A: The first matrix.
 * @param B: The second matrix.
 * @param row: The row index of matrix A.
 * @param col: The column index of matrix B.
 *
 * @return: The result of multiplying the row of matrix A with the column of matrix B.
 */
int multiply_row_col(Matrix* A, Matrix* B, int row, int col) {
    int result = 0;
    for (int k = 0; k < A->cols; k++) 
    {
        result += A->values[row][k] * B->values[k][col];
    }
    return result;
}

/**
 * Function: createMatrix
 * ----------------------
 * Creates a new Matrix with the specified number of rows and columns.
 *
 * @param rows: The number of rows for the new Matrix.
 * @param cols: The number of columns for the new Matrix.
 *
 * @return: A pointer to the newly created Matrix. The Matrix's values are
 *          uninitialized and should be set before use.
 */
Matrix* createMatrix(int rows, int cols) {
    // Allocate memory for the new Matrix structure
    Matrix *matrix = malloc(sizeof(Matrix));

    // Set the number of rows and columns
    matrix->rows = rows;
    matrix->cols = cols;

    // Allocate memory for the 'values' 2D array
    matrix->values = malloc(rows * sizeof(int *));

    // Allocate memory for each row in the 'values' 2D array
    for (int i = 0; i < rows; i++) {
        matrix->values[i] = malloc(cols * sizeof(int));
    }

    // Return the newly created Matrix
    return matrix;
}