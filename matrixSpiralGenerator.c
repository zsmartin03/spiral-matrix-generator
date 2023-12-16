#include <stdio.h>
#include <stdlib.h>

char getNextDirection(char direction, int rotationDirection) {
    if (rotationDirection == 0) {
        switch (direction) {
            case 'r':
                return 'd';
            case 'd':
                return 'l';
            case 'l':
                return 'u';
            case 'u':
                return 'r';
        }
    } else {
        switch (direction) {
            case 'l':
                return 'd';
            case 'd':
                return 'r';
            case 'r':
                return 'u';
            case 'u':
                return 'l';
        }
    }
}

void generateSpiral(int **matrix, int size, char startDirection, int rotationDirection) {

    char direction = startDirection;
    int row = size / 2;
    int column = size / 2;

    if(size % 2 == 0) {
        if((direction == 'r' && rotationDirection == 0) || (direction == 'd' && rotationDirection == 1)) {
            column--;
            row--;
        }
        else if((direction == 'r' && rotationDirection == 1) || (direction == 'u' && rotationDirection == 0)) {
            column--;
        }
        else if((direction == 'd' && rotationDirection == 0) || (direction == 'l' && rotationDirection == 1)) {
            row--;
        }
    }
    int value = 1;
    matrix[row][column] = value;
    value++;
    int moveAmount = 1;
    int moveCounter = 0;

    while(value <= (size * size)) {
        if (moveAmount < (size - 1)) {
            if (moveCounter == 2) {
                moveAmount++;
                moveCounter = 0;
            }
        }

        for (int i = 0; i < moveAmount; i++) {
            if (direction == 'r') {
                column++;
                matrix[row][column] = value; 
            }
            if (direction == 'd') {
                row++;
                matrix[row][column] = value;
            }
            if (direction == 'l') {
                column--;
                matrix[row][column] = value;
            }
            if (direction == 'u') {
                row--;
                matrix[row][column] = value;
            }
            value++;
        }
        direction = getNextDirection(direction, rotationDirection);
        moveCounter++;

        if(value > (size * size)) {
            break;  // mukodik enelkul is, csak biztos ami biztos
        }
    }
}