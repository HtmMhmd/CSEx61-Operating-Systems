#include "readtxt.h"

int main(int argc, char *argv[]){
    // variables for storing the columns number and rows number
    int columns_number, rows_number;

    char *file1 = (argc > 1) ? argv[1] : "../../test1/a.txt";
    
    Matrix *A = read_matrix(file1);
    rows_number     = A->rows;
    columns_number  = A->cols;

    printf("NUMBER OF COLUMNS : %d \n", columns_number);
    printf("NUMBER OF ROWS    : %d \n", rows_number);
    for(int i =0; i < rows_number; i++){
        for(int j =0; j < columns_number; j++){
            printf("%d ", (A->values[i][j]));
    }
        printf("\n");
    }

    return 0;
}