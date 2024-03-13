#include "../utilis/utilis.h"

#ifndef READTXT_H
#define READTXT_H

Matrix *read_matrix(char *filename);
void    open_txt_File(char *filename, FILE **file);
void    store_values_in_txt_into(Matrix *matrix, FILE **file);

#endif // READTXT_H