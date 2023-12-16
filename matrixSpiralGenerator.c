#include <stdio.h>
#include <stdlib.h>

char getNextDirection(char direction, int rotate_dir) {
    if (rotate_dir == 0) {
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

void generateSpiral(int **A, int N, char start_pos, int rotate_dir) {

    char direction = start_pos;
    int sor = N / 2;
    int oszlop = N / 2;
    
    if(N % 2 == 0) {
        if((direction == 'r' && rotate_dir == 0) || (direction == 'd' && rotate_dir == 1)) {
            oszlop--;
            sor--;
        }
        else if((direction == 'r' && rotate_dir == 1) || (direction == 'u' && rotate_dir == 0)) {
            oszlop--;
        }
        else if((direction == 'd' && rotate_dir == 0) || (direction == 'l' && rotate_dir == 1)) {
            sor--;
        }
    }
    A[sor][oszlop] = 1;
    int moveAmount = 1;
    int moveCounter = 0;
    for (int value = 2; value <= (N * N);) {
        if (moveAmount < (N - 1)) {
            if (moveCounter == 2) {
                moveAmount++;
                moveCounter = 0;
            }
        }

        for (int i = 0; i < moveAmount; i++) {
            if (direction == 'r') {
                oszlop++;
                A[sor][oszlop] = value; 
            }
            if (direction == 'd') {
                sor++;
                A[sor][oszlop] = value;
            }
            if (direction == 'l') {
                oszlop--;
                A[sor][oszlop] = value;
            }
            if (direction == 'u') {
                sor--;
                A[sor][oszlop] = value;
            }
            value++;
        }
        direction = getNextDirection(direction, rotate_dir);
        moveCounter++;     
    }
}