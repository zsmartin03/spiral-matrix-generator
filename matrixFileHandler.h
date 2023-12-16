#ifndef MATRIX_FILEHANDLER_H
#define MATRIX_FILEHANDLER_H

void saveMatrixToFile(int **matrix, int size, char startDirection, int rotationDirection);

void readMatrixFromFile(int ***matrix, int *size, char *startDirection, int *rotationDirection);

#endif
