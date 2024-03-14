#include "matrixmul.h"
/**
 * Function: multiply_matrix
 * -------------------------
 * Multiplies two matrices and stores the result in a new matrix.
 *
 * @param arg: Unused argument .
 *
 * @return: A pointer to a struct containing the result matrix .
 */
void *multiply_matrix(void *arg) {
    if (matrices.matrix1 == NULL || matrices.matrix2 == NULL) {
        return NULL;
    }

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
 *`
 * @param arg: The row index to multiply.
 *
 * @return: A pointer to a struct containing the result matrix and its data.
 */
void *multiply_row(void *arg) {
    if (matrices.matrix1 == NULL || matrices.matrix2 == NULL) {
        return NULL;
    }

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
    if (matrices.matrix1 == NULL || matrices.matrix2 == NULL) {
        return NULL;
    }

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