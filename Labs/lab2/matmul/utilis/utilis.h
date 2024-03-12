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
    int rows;
    int cols;
    int **values;
} Matrix;

void *multiply_matrix(void *arg);
void *multiply_row(void *arg);
void *multiply_element(void *arg);

#endif