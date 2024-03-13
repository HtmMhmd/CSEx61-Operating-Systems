#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef UTILIS_H
#define UTILIS_H

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    // variables to store the number of rows and number of columns in 2d matrix
    int rows;
    int cols;
    // dynamically allocated 2d array to store the matrix values
    int **values;
} Matrix;

void *multiply_matrix(void *arg);
void *multiply_row(void *arg);
void *multiply_element(void *arg);

#endif