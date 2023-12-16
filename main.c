#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "matrixSpiralGenerator.h"
#include "matrixFileHandler.h"

void clearInputBuffer();

void backToTheMenu()
{
    char c;
    printf("Type any character to go back to the menu: \n");
    fgets(&c, sizeof(c), stdin);
    clearInputBuffer();
}

int** matrixGeneration(int *dimension, int input, char *startDirection, int *rotationDirection)
{
    int **matrix = NULL;

    if (input == -1)
    {
        clearInputBuffer();
        do
        {
            printf("Enter the dimension of the matrix (1-20): \n");
            char inputDimension[50];
            fgets(inputDimension, sizeof(inputDimension), stdin);
            if (sscanf(inputDimension, "%d", dimension) != 1)
            {
                printf("Invalid input! Please enter an integer value.\n");
                continue;
            }
            if (*dimension < 1 || *dimension > 20)
            {
                printf("Invalid input! The value of the dimension must be between 1 and 20!\n");
            }
        } while (*dimension < 1 || *dimension > 20);

        char inputDirection[2];
        do
        {
            printf("Enter the starting direction of the matrix (l - left, u - up, r - right, d - down): \n");
            fgets(inputDirection, sizeof(inputDirection), stdin);
            *startDirection = inputDirection[0];
        } while (!(*startDirection == 'l' || *startDirection == 'u' || *startDirection == 'r' || *startDirection == 'd'));

        
        do {
            printf("Enter the rotation direction of the matrix (0 - clockwise, 1 - counter clockwise): \n");
            char inputRotation[2];
            fgets(inputRotation, sizeof(inputRotation), stdin);
            *rotationDirection = atoi(inputRotation);
            if (!(*rotationDirection == 0 || *rotationDirection == 1))
            {
                printf("Invalid input! Please enter 0 or 1.\n");
            }
        } while (!(*rotationDirection == 0 || *rotationDirection == 1));
    }



    matrix = (int **)malloc(*dimension * sizeof(int *));
    if (matrix == NULL)
    {
        printf("Memory allocation failed for rows.\n");
        exit(1);
    }

    for (int i = 0; i < *dimension; i++)
    {
        matrix[i] = (int *)malloc(*dimension * sizeof(int));
        if (matrix[i] == NULL)
        {
            printf("Memory allocation failed for columns.\n");
            exit(1);
        }
    }

    if (input == -1)
    {
        generateSpiral(matrix, *dimension, *startDirection, *rotationDirection);
    }
    return matrix;
}

void printMatrix(int **matrix, int dimension)
{
    if(dimension == 0) {
        printf("There is no matrix to print.\n");
        return;
    }
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
    printf(" ___________________________________________ \n");
    printf("|                                           |\n");
    printf("|          Spiral Matrix Generator          |\n");
    printf("|                Users Guide                |\n");
    printf("|                                           |\n");
    printf("| This is a program where you can generate  |\n");
    printf("| spiral matrices.                          |\n");
    printf("|                                           |\n");
    printf("| In the menu you can choose between six    |\n");
    printf("| options.                                  |\n");
    printf("| You are currently in the first option the |\n");
    printf("| user guide.                               |\n");
    printf("| By choosing the second option, you can    |\n");
    printf("| generate your matrix by choosing its      |\n");
    printf("| dimension (1-20), its starting rotation   |\n");
    printf("| and the direction it rotates.             |\n");
    printf("| Under the third and fourth options you    |\n");
    printf("| have the ability to save your matrix to a |\n");
    printf("| file (it will have its dimension and      |\n");
    printf("| rotation parameters in its name), or to   |\n");
    printf("| load a matrix from a file to the current  |\n");
    printf("| session.                                  |\n");
    printf("| If you want to print your matrix to the   |\n");
    printf("| terminal, you can do it by choosing the   |\n");
    printf("| fifth option.                             |\n");
    printf("| You can exit the program by choosing the  |\n");
    printf("| sixth option.                             |\n");
    printf("|                                           |\n");
    printf("| Whenever the program asks you to type any |\n");
    printf("| character to go back to the menu, you     |\n");
    printf("| need to type in any text and then press   |\n");
    printf("| the enter.                                |\n");
    printf("|                                           |\n");
    printf("|___________________________________________|\n");
}

void chosenMenuAction(char chosenMenuOption, int ***matrix, int *dimension, char *startDirection, int *rotationDirection)
{
    switch (chosenMenuOption)
    {
    case '1':
        userGuide();
        backToTheMenu();
        break;
    case '2':
        freeMatrix(matrix, *dimension);
        *matrix = matrixGeneration(dimension, -1, startDirection, rotationDirection);
        break;
    case '3':
        saveMatrixToFile(*matrix, *dimension, *startDirection, *rotationDirection);
        break;
    case '4':
        readMatrixFromFile(matrix, dimension, startDirection, rotationDirection);
        backToTheMenu();
        break;
    case '5':
        printMatrix(*matrix, *dimension);
        backToTheMenu();
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
    char startDirection;
    int rotationDirection = -1; // 0 - clockwise, 1 - counter clockwise
    int **newMatrix = matrixGeneration(&matrixDimension, matrixDimension, &startDirection, &rotationDirection);

    while (1)
    {
        chosenMenuAction(menu(), &newMatrix, &matrixDimension, &startDirection, &rotationDirection);
    }

    return 0;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
