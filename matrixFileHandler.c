#include <stdio.h>
#include <stdlib.h>

void saveMatrixToFile(int **matrix, int size, char startDirection,
                      int rotationDirection) {
  if (size == 0) {
    printf("There is no matrix to save.\n");
    return;
  }

  char filename[20];
  sprintf(filename, "spiral_%d_%c_%d.txt", size, startDirection,
          rotationDirection);

  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    printf("Error saving the file.\n");
    return;
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (size < 4) {
        fprintf(file, "%d ", matrix[i][j]);
      } else if (size < 10) {
        fprintf(file, "%2d ", matrix[i][j]);
      } else {
        fprintf(file, "%3d ", matrix[i][j]);
      }
    }
    fprintf(file, "\n");
  }

  fclose(file);
  printf("Matrix saved successfully.\n");
}

void readMatrixFromFile(int ***matrix, int *size, char *startDirection,
                        int *rotationDirection) {
  char filename[20];
  printf("Enter the filename (with the .txt): ");
  scanf("%19s", filename);

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error opening file.\n");
    return;
  }

  int newSize, newRotationDirection;
  char newStartDirection;
  if (sscanf(filename, "spiral_%d_%c_%d.txt", &newSize, &newStartDirection,
             &newRotationDirection) != 3) {
    printf("Invalid filename format.\n");
    fclose(file);
    return;
  }

  int **newMatrix = (int **)malloc(newSize * sizeof(int *));
  if (newMatrix == NULL) {
    printf("Memory allocation failed.\n");
    fclose(file);
    return;
  }

  for (int i = 0; i < newSize; i++) {
    newMatrix[i] = (int *)malloc(newSize * sizeof(int));
    if (newMatrix[i] == NULL) {
      printf("Memory allocation failed.\n");
      for (int j = 0; j < i; j++) {
        free(newMatrix[j]);
      }
      free(newMatrix);
      fclose(file);
      return;
    }
  }

  for (int i = 0; i < newSize; i++) {
    for (int j = 0; j < newSize; j++) {
      if (fscanf(file, "%d", &(newMatrix[i][j])) != 1) {
        printf("File reading error.\n");
        for (int k = 0; k < newSize; k++) {
          free(newMatrix[k]);
        }
        free(newMatrix);
        fclose(file);
        return;
      }
    }
  }

  for (int i = 0; i < *size; i++) {
    free((*matrix)[i]);
  }
  free(*matrix);

  *matrix = newMatrix;
  *size = newSize;
  *startDirection = newStartDirection;
  *rotationDirection = newRotationDirection;

  fclose(file);
  printf("Matrix loaded successfully.\n");
}
