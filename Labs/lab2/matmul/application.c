#include "application.h"

int main(int argc, char *argv[]) 
{

    char *file1 = (argc > 1) ? argv[1] : "../test1/a.txt";
    char *file2 = (argc > 2) ? argv[2] : "../test1/b.txt";
    //char *file3 = (argc > 3) ? argv[3] : "c";

    Matrix *A = read_matrix(file1);
    Matrix *B = read_matrix(file2);
    //=========================BEGAIN TEST===================================
    int columns_number, rows_number;

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
    //=========================END   TEST===================================

    //=========================BEGAIN TEST===================================
    rows_number     = B->rows;
    columns_number  = B->cols;

    printf("NUMBER OF COLUMNS : %d \n", columns_number);
    printf("NUMBER OF ROWS    : %d \n", rows_number);
    for(int i =0; i < rows_number; i++){
        for(int j =0; j < columns_number; j++){
            printf("%d ", (B->values[i][j]));
    }
        printf("\n");
    }
    //=========================END   TEST===================================
    MyStructs structs = {A, B};
    // A thread per matrix
    pthread_t thread;
    pthread_create(&thread, NULL, multiply_matrix, &structs);
    pthread_join(thread, NULL);

    // A thread per row
    // for (int i = 0; i < A->rows; i++) {
    //     pthread_create(&thread, NULL, multiply_row, (void *)(long)i);
    // }
    // pthread_join(thread, NULL);

    // A thread per element
    // for (int i = 0; i < A->rows; i++) {
    //     for (int j = 0; j < B->cols; j++) {
    //         pthread_create(&thread, NULL, multiply_element, (void *)(long)(i * B->cols + j));
    //     }
    // }
    // pthread_join(thread, NULL);

    return 0;
}

void *multiply_matrix(void *arg) {
    MyStructs* structs = (MyStructs*)arg;
    Matrix *A, *B;
    A = structs->struct1;
    B = structs->struct2;
    // Matrix *A = ((Matrix **)arg)[0];
    // Matrix *B = ((Matrix **)arg)[1];
    Matrix *C = malloc(sizeof(Matrix));

    C->rows = A->rows;
    C->cols = B->cols;
    C->values = malloc(C->rows * sizeof(int *));
    for (int i = 0; i < C->rows; i++) {
        C->values[i] = malloc(C->cols * sizeof(int));
        for (int j = 0; j < C->cols; j++) {
            C->values[i][j] = 0;
            for (int k = 0; k < A->cols; k++) {
                C->values[i][j] += A->values[i][k] * B->values[k][j];
            }
        }
    }
    //=========================BEGAIN TEST===================================
    int columns_number, rows_number;

    rows_number     = C->rows;
    columns_number  = C->cols;

    printf("NUMBER OF COLUMNS : %d \n", columns_number);
    printf("NUMBER OF ROWS    : %d \n", rows_number);
    for(int i =0; i < rows_number; i++){
        for(int j =0; j < columns_number; j++){
            printf("%d ", (C->values[i][j]));
    }
        printf("\n");
    }
    //=========================END   TEST===================================
    return C;
}

void *multiply_row(void *arg) {
    int row = (int)arg;
    Matrix *A = ((Matrix **)arg)[0];
    Matrix *B = ((Matrix **)arg)[1];
    Matrix *C = malloc(sizeof(Matrix));
    C->rows = 1;
    C->cols = B->cols;
    C->values = malloc(sizeof(int *));
    C->values[0] = malloc(C->cols * sizeof(int));
    for (int j = 0; j < C->cols; j++) {
        C->values[0][j] = 0;
        for (int k = 0; k < A->cols; k++) {
            C->values[0][j] += A->values[row][k] * B->values[k][j];
        }
    }
    return C;
}

void *multiply_element(void *arg) {
    int row = (int)arg / ((Matrix **)arg)[1]->cols;
    int col = (int)arg % ((Matrix **)arg)[1]->cols;
    Matrix *A = ((Matrix **)arg)[0];
    Matrix *B = ((Matrix **)arg)[1];
    int *value = malloc(sizeof(int));
    *value = 0;
    for (int k = 0; k < A->cols; k++) {
        *value += A->values[row][k] * B->values[k][col];
    }
    return value;
}