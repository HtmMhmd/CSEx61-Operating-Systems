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
/** define type struct Matrix to store the matrix
* variables to store the number of rows and number of columns in 2d matrix
* dynamically allocated 2d array to store the matrix values
*/
typedef struct {
    
    int rows;
    int cols;
    int **values;
} Matrix;

typedef enum {
    READ_TXT ,
    WRITE_TXT
} open_file_t;
/*======================================================================================*/
/*                              FUNCTIONS DEFINITIONS                                   */
/*======================================================================================*/

/**
 * Opens the txt file.
 *
 * @param filename   : string (path) of the txt file.
 * @param open_type  : enum indicating the type of file operation.
 * @return file      : pointer to the opened file.
 */
FILE *open_txt_File(char *filename, open_file_t open_type);

#endif