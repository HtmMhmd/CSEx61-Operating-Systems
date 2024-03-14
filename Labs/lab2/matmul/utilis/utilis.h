#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef UTILIS_H
#define UTILIS_H
/*======================================================================================*/
/*                              MACRO DEFINITIONS                                       */
/*======================================================================================*/

// define NULL if not defined
// to overcome some warnings during coding
#ifndef NULL
#define NULL 0
#endif

/*======================================================================================*/
/*                              TYPES DEFINITIONS                                       */
/*======================================================================================*/
// define type struct Matrix to store the matrix
typedef struct {
    // variables to store the number of rows and number of columns in 2d matrix
    int rows;
    int cols;
    // dynamically allocated 2d array to store the matrix values
    int **values;
} Matrix;

typedef enum {
    READ_TXT ,
    WRITE_TXT
} open_file_t;
/*======================================================================================*/
/*                              FUNCTIONS DEFINITIONS                                   */
/*======================================================================================*/
void open_txt_File(char *filename, FILE **file, open_file_t open_type);

#endif