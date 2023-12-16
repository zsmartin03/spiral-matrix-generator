#include <stdio.h>
#include <stdlib.h>

void saveMatrixToFile(int **matrix, int size, char startDirection, int rotationDirection) {
    char filename[20];
    sprintf(filename, "spiral_%d_%c_%d.txt", size, startDirection, rotationDirection);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error saving the file.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (size < 4)
            {
                fprintf(file, "%d ", matrix[i][j]);
            }
            else if (size < 10)
            {
                fprintf(file, "%2d ", matrix[i][j]);
            }
            else
            {
                fprintf(file, "%3d ", matrix[i][j]);
            }

        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void readMatrixFromFile(int ***matrix, int *size, char *startDirection, int *rotationDirection) {
    char filename[20];
    printf("Enter the filename (with the .txt): ");
    scanf("%s", filename);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < *size; i++)
    {
        free((*matrix)[i]);
    }
    free(*matrix);
    *matrix = NULL;

    sscanf(filename, "spiral_%d_%c_%d.txt", size, startDirection, rotationDirection);

    *matrix = (int **)malloc(*size * sizeof(int *));
    for (int i = 0; i < *size; i++) {
        (*matrix)[i] = (int *)malloc(*size * sizeof(int));
    }

    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < *size; j++) {
            fscanf(file, "%d", &((*matrix)[i][j]));
        }
    }
    fclose(file);
    printf("Matrix loaded successfully.\n");
}
