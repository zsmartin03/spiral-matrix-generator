#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

typedef struct {
    int** matrix;
    int dimension;
} MatrixInfo;

void generateSpiralMatrix(int dimension, char startDirection, int rotationDirection, int** matrix) {
    int i, top = 0, bottom = dimension - 1, left = 0, right = dimension - 1;
    int direction;

    switch (startDirection) {
        case 'l':
            direction = 2; // left
            break;
        case 'u':
            direction = 3; // up
            break;
        case 'r':
            direction = 0; // right
            break;
        case 'd':
            direction = 1; // down
            break;
        default:
            fprintf(stderr, "Invalid starting direction.\n");
            exit(EXIT_FAILURE);
    }

    for (i = 1; i <= dimension * dimension; ++i) {
        matrix[top][left] = i;

        switch (direction) {
            case 0: // right
                left++;
                break;
            case 1: // down
                top++;
                break;
            case 2: // left
                right--;
                break;
            case 3: // up
                bottom--;
                break;
        }

        // Change direction based on rotationDirection
        if (rotationDirection == 1) {
            direction = (direction + 1) % 4;
        } else {
            direction = (direction + 3) % 4;
        }

        // Adjust indices to stay within bounds
        if (left > right || top > bottom) {
            break;
        }
    }
}

MatrixInfo matrixGeneration(int input) {
    MatrixInfo matrixInfo;
    int dimension = 0;
    char startDirection;
    int rotationDirection = 2; // 0 - clockwise, 1 - counter clockwise
    if(input == -1) {
      while (getchar() != '\n');
      while(!(dimension >= 1 && dimension <= 20)) {
        printf("Enter the dimension of the matrix (1-20): \n");
        if (scanf(" %d", &dimension) != 1) {
          while (getchar() != '\n');
        }
        if(dimension < 1 || dimension > 20) {
          printf("Invalid input! The value of the dimension must be between 1 and 20!\n");
        }
      }

      while(!(startDirection == 'l' || startDirection == 'u' || startDirection == 'r' || startDirection == 'd')) {
        printf("Enter the starting direction of the matrix (l - left, u - up, r - right, d - down): \n");
        scanf(" %c", &startDirection);
      }
      while(!(rotationDirection == 0 || rotationDirection == 1)) {
        printf("Enter the rotation direction of the matrix (0 - clockwise, 1 - counter clockwise): \n");
        scanf("%d", &rotationDirection);
      }
    }

    matrixInfo.matrix = NULL;
    matrixInfo.dimension = dimension;

    matrixInfo.matrix = (int**)malloc(matrixInfo.dimension * sizeof(int*));
    if (matrixInfo.matrix == NULL) {
        fprintf(stderr, "Memory allocation failed for rows.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < matrixInfo.dimension; i++) {
        matrixInfo.matrix[i] = (int*)malloc(matrixInfo.dimension * sizeof(int));
        if (matrixInfo.matrix[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for columns.\n");
            exit(EXIT_FAILURE);
        }
    }
    
    if(input == -1) {
    generateSpiralMatrix(matrixInfo.dimension, startDirection, rotationDirection, matrixInfo.matrix);
    }
    return matrixInfo;
}

void printMatrix(MatrixInfo matrixInfo) {
  char c;
      for (int i = 0; i < matrixInfo.dimension; i++) {
        for (int j = 0; j < matrixInfo.dimension; j++) {
            if(matrixInfo.dimension < 4) {
              printf("%d ", matrixInfo.matrix[i][j]);
            }
            else if(matrixInfo.dimension < 10) {
              printf("%2d ", matrixInfo.matrix[i][j]);
            }
            else {
              printf("%3d ", matrixInfo.matrix[i][j]);
            }
        }
      printf("\n");
    }
  printf("Type any character to go back to the menu: \n");
  scanf(" %c", &c);
}

void freeMatrix(MatrixInfo* matrixInfo) {
    for (int i = 0; i < matrixInfo->dimension; i++) {
        free(matrixInfo->matrix[i]);
    }
    free(matrixInfo->matrix);
}
void userGuide() {
  char c;
  printf("\e[1;1H\e[2J"); 
  printf("This is a program where you can generate spiral matrixes.\n");
  printf("#2 Matrix Generation: Here you can...\n");
  printf("#3 You can save your generated matrixes here\n");
  printf("#4 In this you can load an existing..\n");
  printf("Type any character to go back to the menu: \n");
  scanf(" %c", &c);
}

void chosenMenuAction(char chosenMenuOption, MatrixInfo* matrixInfo) {
    switch (chosenMenuOption) {
        case '1':
            userGuide();
            break;
        case '2':
            freeMatrix(matrixInfo);
            *matrixInfo = matrixGeneration(-1);
            break;
        case '3':
            printf("Save\n");
            break;
        case '4':
            printf("Load\n");
            break;
        case '5':
            printMatrix(*matrixInfo);
            break;
        case '6':
            freeMatrix(matrixInfo);
            exit(0);
            break;
    }
}

int main() {
    int initialDimension = 0; 
    MatrixInfo myMatrixInfo = matrixGeneration(initialDimension);

    while (1) {
        chosenMenuAction(menu(), &myMatrixInfo);
    }

    return 0;
}

