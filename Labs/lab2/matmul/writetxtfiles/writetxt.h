#include "../utilis/utilis.h"

#ifndef WRITETXT_H
#define WRITETXT_H

/*======================================================================================*/
/*                              FUNCTIONS DEFINITIONS                                   */
/*======================================================================================*/

/**
 * Writes the matrix in the format presented in the test cases to a text file.
 *
 * @param filename - The path of the file where the formatted matrix will be saved.
 * @param matrix - A pointer to the Matrix struct containing the matrix data.
 */
void write_matrix(char *filename, Matrix *matrix);

#endif