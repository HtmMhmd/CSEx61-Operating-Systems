#include "../utilis/utilis.h"

#ifndef READTXT_H
#define READTXT_H

/*======================================================================================*/
/*                              FUNCTIONS DEFINITIONS                                   */
/*======================================================================================*/

Matrix *read_matrix(char *filename);
void    store_values_in_txt_into(Matrix *matrix, FILE **file);

#endif 