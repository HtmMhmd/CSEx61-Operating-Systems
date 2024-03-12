#include "writetxt.h"

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