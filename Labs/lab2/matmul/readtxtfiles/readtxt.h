#include "../utilis/utilis.h"

#ifndef READTXT_H
#define READTXT_H

/*======================================================================================*/
/*                              FUNCTIONS DEFINITIONS                                   */
/*======================================================================================*/

/**
 * Reads matrix in the format presented in the test cases.
 *
 * @param filename : string (path) which the formatted matrix presents.
 * @return matrix  : struct of cols, rows, values.
 */
Matrix *read_matrix(char *filename);

/**
 * Stores values in the input txt into matrix.
 *
 * @param matrix : pointer to struct of type Matrix (to use dynamic memory allocation).
 * @param file   : pointer to a FILE type (to use dynamic memory allocation).
 */
void    store_values_in_txt_into(Matrix *matrix, FILE *file);

#endif 