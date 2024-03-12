#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int rows;
    int cols;
    int **values;
} Matrix;

Matrix *read_matrix(char *filename);
void write_matrix(char *filename, Matrix *matrix);
void *multiply_matrix(void *arg);
void *multiply_row(void *arg);
void *multiply_element(void *arg);

int main(int argc, char *argv[]) {
    char *file1 = (argc > 1) ? argv[1] : "a.txt";
    char *file2 = (argc > 2) ? argv[2] : "b.txt";
    char *file3 = (argc > 3) ? argv[3] : "c";

    Matrix *A = read_matrix(file1);
    Matrix *B = read_matrix(file2);

    // A thread per matrix
    pthread_t thread;
    pthread_create(&thread, NULL, multiply_matrix, NULL);
    pthread_join(thread, NULL);

    // A thread per row
    for (int i = 0; i < A->rows; i++) {
        pthread_create(&thread, NULL, multiply_row, (void *)(long)i);
    }
    pthread_join(thread, NULL);

    // A thread per element
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->cols; j++) {
            pthread_create(&thread, NULL, multiply_element, (void *)(long)(i * B->cols + j));
        }
    }
    pthread_join(thread, NULL);

    return 0;
}

Matrix *read_matrix(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cannot open file %s\n", filename);
        exit(1);
    }

    Matrix *matrix = malloc(sizeof(Matrix));
    fscanf(file, "row=%d col=%d", &matrix->rows, &matrix->cols);

    matrix->values = malloc(matrix->rows * sizeof(int *));
    for (int i = 0; i < matrix->rows; i++) {
        matrix->values[i] = malloc(matrix->cols * sizeof(int));
        for (int j = 0; j < matrix->cols; j++) {
            fscanf(file, "%d", &matrix->values[i][j]);
        }
    }

    fclose(file);
    return matrix;
}

void write_matrix(char *filename, Matrix *matrix) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Cannot open file %s\n", filename);
        exit(1);
    }

    fprintf(file, "row=%d col=%d\n", matrix->rows, matrix->cols);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            fprintf(file, "%d ", matrix->values[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void *multiply_matrix(void *arg) {
    Matrix *A = ((Matrix **)arg)[0];
    Matrix *B = ((Matrix **)arg)[1];
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