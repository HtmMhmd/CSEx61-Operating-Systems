#include "readtxtfiles/readtxt.h"
#include "writetxtfiles/writetxt.h"

#ifndef APPLICATION_H
#define APPLICATION_H

void *multiply_matrix(void *arg);
void *multiply_row(void *arg);
void *multiply_element(void *arg);

typedef struct {
Matrix** struct1;
Matrix** struct2;
} MyStructs;

#endif