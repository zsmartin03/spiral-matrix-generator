#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "matrixSpiralGenerator.h"

typedef struct
{
    int **matrix;
    int dimension;
} MatrixInfo;

void clearInputBuffer();

MatrixInfo matrixGeneration(int input)
{
    MatrixInfo matrixInfo;
    int dimension = 0;
    char startDirection;
    int rotationDirection; // 0 - clockwise, 1 - counter clockwise
    if (input == -1)
    {
        clearInputBuffer();
        do
        {
            printf("Enter the dimension of the matrix (1-20): \n");
            if (scanf(" %d", &dimension) != 1)
            {
                printf("Invalid input! Please enter an integer.\n");
                clearInputBuffer();
            }
            else if (dimension < 1 || dimension > 20)
            {
                printf("Invalid input! The value of the dimension must be between 1 and 20!\n");
            }
        } while (dimension < 1 || dimension > 20);

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

    matrixInfo.matrix = NULL;
    matrixInfo.dimension = dimension;

    matrixInfo.matrix = (int **)malloc(matrixInfo.dimension * sizeof(int *));
    if (matrixInfo.matrix == NULL)
    {
        fprintf(stderr, "Memory allocation failed for rows.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < matrixInfo.dimension; i++)
    {
        matrixInfo.matrix[i] = (int *)malloc(matrixInfo.dimension * sizeof(int));
        if (matrixInfo.matrix[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for columns.\n");
            exit(EXIT_FAILURE);
        }
    }

    if (input == -1)
    {
        generateSpiral(matrixInfo.matrix, matrixInfo.dimension, startDirection, rotationDirection);
    }
    return matrixInfo;
}

void printMatrix(MatrixInfo matrixInfo)
{
    char c;
    for (int i = 0; i < matrixInfo.dimension; i++)
    {
        for (int j = 0; j < matrixInfo.dimension; j++)
        {
            if (matrixInfo.dimension < 4)
            {
                printf("%d ", matrixInfo.matrix[i][j]);
            }
            else if (matrixInfo.dimension < 10)
            {
                printf("%2d ", matrixInfo.matrix[i][j]);
            }
            else
            {
                printf("%3d ", matrixInfo.matrix[i][j]);
            }
        }
        printf("\n");
    }
    printf("Type any character to go back to the menu: \n");
    scanf(" %c", &c);
    clearInputBuffer();
}

void freeMatrix(MatrixInfo *matrixInfo)
{
    for (int i = 0; i < matrixInfo->dimension; i++)
    {
        free(matrixInfo->matrix[i]);
    }
    free(matrixInfo->matrix);
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

void chosenMenuAction(char chosenMenuOption, MatrixInfo *matrixInfo)
{
    switch (chosenMenuOption)
    {
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

int main()
{
    int initialDimension = 0;
    MatrixInfo myMatrixInfo = matrixGeneration(initialDimension);

    while (1)
    {
        chosenMenuAction(menu(), &myMatrixInfo);
    }

    return 0;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}