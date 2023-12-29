#include "matrixFileHandler.h"
#include "matrixSpiralGenerator.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearInputBuffer();

void backToTheMenu();

int **matrixGeneration(int *size, int input, char *startDirection,
                       int *rotationDirection) {
  int **matrix = NULL;

  int newSize = 0;
  clearInputBuffer();
  do {
    printf("Enter the dimension of the matrix (1-20): \n");
    if (scanf(" %d", &newSize) != 1) {
      printf("Invalid input! Please enter an integer.\n");
      clearInputBuffer();
    } else if (newSize < 1 || newSize > 20) {
      printf("Invalid input! The value of the dimension must be between 1 "
             "and 20!\n");
    }

  } while (newSize < 1 || newSize > 20);
  *size = newSize;

  clearInputBuffer();

  char inputDirection[3];
  char newDirection;
  do {
    printf("Enter the starting direction of the matrix (l - left, u - up, r "
           "- right, d - down): \n");
    fgets(inputDirection, sizeof(inputDirection), stdin);
    if (inputDirection[1] != '\n') {
      printf("Invalid input! Please enter a single character.\n");
      if (strlen(inputDirection) % 2 == 0) {
        clearInputBuffer();
      }
    } else {
      switch (inputDirection[0]) {
      case 'l':
      case 'u':
      case 'r':
      case 'd':
        newDirection = inputDirection[0];
        break;
      default:
        printf("Invalid input! Please enter l, u, r, or d.\n");
      }
    }
  } while (!(newDirection == 'l' || newDirection == 'u' ||
             newDirection == 'r' || newDirection == 'd'));

  *startDirection = newDirection;

  int newRotationDirection = -1;

  do {
    printf("Enter the rotation direction of the matrix (0 - clockwise, 1 - "
           "counter clockwise): \n");
    if (scanf(" %d", &newRotationDirection) != 1) {
      printf("Invalid input! Please enter an integer.\n");
      clearInputBuffer();
    } else if (!(newRotationDirection == 0 || newRotationDirection == 1)) {
      printf("Invalid input! Please enter 0 or 1.\n");
    }
  } while (!(newRotationDirection == 0 || newRotationDirection == 1));

  *rotationDirection = newRotationDirection;

  matrix = (int **)malloc(*size * sizeof(int *));
  if (matrix == NULL) {
    printf("Memory allocation failed for rows.\n");
    exit(1);
  }

  for (int i = 0; i < *size; i++) {
    matrix[i] = (int *)malloc(*size * sizeof(int));
    if (matrix[i] == NULL) {
      printf("Memory allocation failed for columns.\n");
      exit(1);
    }
  }

  generateSpiral(matrix, *size, *startDirection, *rotationDirection);

  return matrix;
}

void printMatrix(int **matrix, int size) {
  if (size == 0) {
    printf("No matrix to print.\n");
    return;
  }
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (size < 4) {
        printf("%d ", matrix[i][j]);
      } else if (size < 10) {
        printf("%2d ", matrix[i][j]);
      } else {
        printf("%3d ", matrix[i][j]);
      }
    }
    printf("\n");
  }
}

void freeMatrix(int ***matrix, int size) {
  for (int i = 0; i < size; i++) {
    free((*matrix)[i]);
  }
  free(*matrix);
  *matrix = NULL;
}

void userGuide() {
  printf("\e[1;1H\e[2J");
  printf("  ___________________________________________ \n");
  printf(" |                                           |\n");
  printf(" |          Spiral Matrix Generator          |\n");
  printf(" |                Users Guide                |\n");
  printf(" |                                           |\n");
  printf(" | This is a program where you can generate  |\n");
  printf(" | spiral matrices.                          |\n");
  printf(" |                                           |\n");
  printf(" | In the menu you can choose between six    |\n");
  printf(" | options.                                  |\n");
  printf(" | You are currently in the first option the |\n");
  printf(" | user guide.                               |\n");
  printf(" | By choosing the second option, you can    |\n");
  printf(" | generate your matrix by choosing its      |\n");
  printf(" | dimension (1-20), its starting rotation   |\n");
  printf(" | and the direction it rotates.             |\n");
  printf(" | Under the third and fourth options you    |\n");
  printf(" | have the ability to save your matrix to a |\n");
  printf(" | file (it will have its dimension and      |\n");
  printf(" | rotation parameters in its name), or to   |\n");
  printf(" | load a matrix from a file to the current  |\n");
  printf(" | session.                                  |\n");
  printf(" | If you want to print your matrix to the   |\n");
  printf(" | terminal, you can do it by choosing the   |\n");
  printf(" | fifth option.                             |\n");
  printf(" | You can exit the program by choosing the  |\n");
  printf(" | sixth option.                             |\n");
  printf(" |                                           |\n");
  printf(" | Whenever the program asks you to type any |\n");
  printf(" | character to go back to the menu, you     |\n");
  printf(" | need to type in any text and then press   |\n");
  printf(" | the enter.                                |\n");
  printf(" |                                           |\n");
  printf(" |___________________________________________|\n");
}

void chosenMenuAction(int chosenMenuOption, int ***matrix, int *size,
                      char *startDirection, int *rotationDirection) {
  switch (chosenMenuOption) {
  case 1:
    userGuide();
    backToTheMenu();
    break;
  case 2:
    freeMatrix(matrix, *size);
    *matrix = matrixGeneration(size, -1, startDirection, rotationDirection);
    break;
  case 3:
    saveMatrixToFile(*matrix, *size, *startDirection, *rotationDirection);
    backToTheMenu();
    break;
  case 4:
    readMatrixFromFile(matrix, size, startDirection, rotationDirection);
    backToTheMenu();
    break;
  case 5:
    printMatrix(*matrix, *size);
    backToTheMenu();
    break;
  case 6:
    freeMatrix(matrix, *size);
    exit(0);
    break;
  }
}

int main() {
  int matrixSize = 0;
  char startDirection;
  int rotationDirection; // 0 - clockwise, 1 - counter clockwise
  int **newMatrix = NULL;

  while (1) {
    chosenMenuAction(menu(), &newMatrix, &matrixSize, &startDirection,
                     &rotationDirection);
  }

  return 0;
}

void clearInputBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void backToTheMenu() {
  char c;
  printf("Type any character to go back to the menu: \n");
  scanf(" %c", &c);
  clearInputBuffer();
}
