#include "readtxtfiles/readtxt.h"
#include "writetxtfiles/writetxt.h"

#ifndef APPLICATION_H
#define APPLICATION_H

/*======================================================================================*/
/*                              TYPES DEFINITIONS                                       */
/*======================================================================================*/
// define type struct MatrixStacked to store the 2 Matrix type variables
// for matrix multiplication
typedef struct 
{
Matrix* matrix1;
Matrix* matrix2;
} MatrixStacked;

typedef struct 
{
int   index_col;
int   index_row;
Matrix* matrix;
} rowMatrix_stdReturn;

typedef struct 
{
int   index_col;
int   index_row;
int  Elemant;
} elemantMatrix_stdReturn;
/*======================================================================================*/
/*                              FUNCTIONS DEFINITIONS                                   */
/*======================================================================================*/
void *multiply_matrix(void *arg);
void *multiply_row(void *arg);
void *multiply_element(void *arg);
Matrix* createMatrix(int rows, int cols);
int multiply_row_col(Matrix* A, Matrix* B, int row, int col);
/*======================================================================================*/
#endif