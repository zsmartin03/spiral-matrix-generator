#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "matrixSpiralGenerator.h"

void clearInputBuffer();

int** matrixGeneration(int *dimension, int input)
{
    int **matrix = NULL;
    char startDirection;
    int rotationDirection = -1; // 0 - clockwise, 1 - counter clockwise
    if (input == -1)
    {
        clearInputBuffer();
        do
        {
            printf("Enter the dimension of the matrix (1-20): \n");
            if (scanf(" %d", dimension) != 1)
            {
                printf("Invalid input! Please enter an integer.\n");
                clearInputBuffer();
            }
            else if (*dimension < 1 || *dimension > 20)
            {
                printf("Invalid input! The value of the dimension must be between 1 and 20!\n");
            }
        } while (*dimension < 1 || *dimension > 20);

        do
        {
            printf("Enter the starting direction of the matrix (l - left, u - up, r - right, d - down): \n");
            if (scanf(" %c", &startDirection) != 1)
            {
                printf("Invalid input! Please enter a character.\n");
                clearInputBuffer();
            }
            else if (!(startDirection == 'l' || startDirection == 'u' || startDirection == 'r' || startDirection == 'd'))
            {
                printf("Invalid input! Please enter l, u, r, or d.\n");
            }
        } while (!(startDirection == 'l' || startDirection == 'u' || startDirection == 'r' || startDirection == 'd'));

        
        do {
            printf("Enter the rotation direction of the matrix (0 - clockwise, 1 - counter clockwise): \n");
            if (scanf(" %d", &rotationDirection) != 1)
            {
                printf("Invalid input! Please enter an integer.\n");
                clearInputBuffer();
            }
            else if (!(rotationDirection == 0 || rotationDirection == 1))
            {
                printf("Invalid input! Please enter 0 or 1.\n");
            }
        } while (!(rotationDirection == 0 || rotationDirection == 1));
    }



    matrix = (int **)malloc(*dimension * sizeof(int *));
    if (matrix == NULL)
    {
        fprintf(stderr, "Memory allocation failed for rows.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *dimension; i++)
    {
        matrix[i] = (int *)malloc(*dimension * sizeof(int));
        if (matrix[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for columns.\n");
            exit(EXIT_FAILURE);
        }
    }

    if (input == -1)
    {
        generateSpiral(matrix, *dimension, startDirection, rotationDirection);
    }
    return matrix;
}

void printMatrix(int **matrix, int dimension)
{
    char c;
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            if (dimension < 4)
            {
                printf("%d ", matrix[i][j]);
            }
            else if (dimension < 10)
            {
                printf("%2d ", matrix[i][j]);
            }
            else
            {
                printf("%3d ", matrix[i][j]);
            }
        }
        printf("\n");
    }
    printf("Type any character to go back to the menu: \n");
    scanf(" %c", &c);
    clearInputBuffer();
}

void freeMatrix(int ***matrix, int dimension)
{
    for (int i = 0; i < dimension; i++)
    {
        free((*matrix)[i]);
    }
    free(*matrix);
    *matrix = NULL;
}

void userGuide()
{
    char c;
    printf("\e[1;1H\e[2J");
    printf("This is a program where you can generate spiral matrixes.\n");
    printf("#2 Matrix Generation: Here you can...\n");
    printf("#3 You can save your generated matrixes here\n");
    printf("#4 In this you can load an existing..\n");
    printf("Type any character to go back to the menu: \n");
    scanf(" %c", &c);
    clearInputBuffer();
}

void chosenMenuAction(char chosenMenuOption, int ***matrix, int *dimension)
{
    switch (chosenMenuOption)
    {
    case '1':
        userGuide();
        break;
    case '2':
        freeMatrix(matrix, *dimension);
        *matrix = matrixGeneration(dimension, -1);
        break;
    case '3':
        printf("Save\n");
        break;
    case '4':
        printf("Load\n");
        break;
    case '5':
        printMatrix(*matrix, *dimension);
        break;
    case '6':
        freeMatrix(matrix, *dimension);
        exit(0);
        break;
    }
}

int main()
{
    int matrixDimension = 0;
    int **newMatrix = matrixGeneration(&matrixDimension, matrixDimension);

    while (1)
    {
        chosenMenuAction(menu(), &newMatrix, &matrixDimension);
    }

    return 0;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}