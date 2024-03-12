#include "readtxt.h"

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