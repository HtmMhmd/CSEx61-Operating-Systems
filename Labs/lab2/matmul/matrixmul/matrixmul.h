
#include "../readtxtfiles/readtxt.h"
#include "../writetxtfiles/writetxt.h"
#ifndef MATRIXMUL_H
#define MATRIXMUL_H

/*======================================================================================*/
/*                              TYPES DEFINITIONS                                       */
/*======================================================================================*/
/**
 *  struct MatrixStacked to store the 2 Matrix type variables for matrix multiplication.
 */
typedef struct 
{
Matrix* matrix1;
Matrix* matrix2;
} MatrixStacked;
/**
 *  struct rowMatrix_stdReturn to store the Matrix row , row index 
 *  for matrix row multiplication
 */
typedef struct 
{
int   index_col;
int   index_row;
Matrix* matrix;
} rowMatrix_stdReturn;
/**
 *  struct elemantMatrix_stdReturn to store the Matrix Elemant row index,columnindex
 *  for matrix elemant multiplication
 */
typedef struct 
{
int   index_col;
int   index_row;
int  Elemant;
} elemantMatrix_stdReturn;
/*======================================================================================*/
/*                              FUNCTIONS DEFINITIONS                                   */
/*======================================================================================*/


/**
 * Function: multiply_matrix
 * 
 * -------------------------
 * Multiplies two matrices and stores the result in a new matrix.
 * @param arg: Unused argument (required for thread function signature).
 * 
 * @return void: A pointer to a struct containing the result matrix .
 */
void *multiply_matrix(void *arg);
/**
 * Function: multiply_row
 * ----------------------
 * Multiplies a row of matrix A with matrix B and stores the result in a new matrix.
 *
 * @param arg: The row index to multiply.
 *
 * @return void: A pointer to a struct containing the result matrix and its data.
 */
void *multiply_row(void *arg);

/**
 * Function: multiply_element
 * --------------------------
 * Multiplies an element of matrix A with matrix B and stores the result.
 *
 * @param arg: The index of the element to multiply.
 *
 * @return void: A pointer to a struct containing the result element and its metadata.
 */
void *multiply_element(void *arg);

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
 * @return void: The result of multiplying the row of matrix A with the column of matrix B.
 */
int multiply_row_col(Matrix* A, Matrix* B, int row, int col);

/**
 * Function: createMatrix
 * ----------------------
 * Creates a new Matrix with the specified number of rows and columns.
 *
 * @param rows: The number of rows for the new Matrix.
 * @param cols: The number of columns for the new Matrix.
 *
 * @return void: A pointer to the newly created Matrix. The Matrix's values are
 *          uninitialized and should be set before use.
 */
Matrix* createMatrix(int rows, int cols);

/*======================================================================================*/
/*                              VARIABLES DEFINITIONS                                       */
/*======================================================================================*/

// global as it's used for read-only access
// it used to store the 2 matrices matrix1, matrix2 to run the multplication on
MatrixStacked matrices;

#endif