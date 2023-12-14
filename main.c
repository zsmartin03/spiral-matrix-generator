#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

void chosenMenuAction(char chosenMenuOption);

int main() {
  chosenMenuAction(menu());

  return 0;
}

void matrixGeneration() {
  int dimension;
  char startDirection;
  char rotationDirection[3]; // 0 - clockwise, 1 - counter

  printf("Enter the dimension of the matrix:\n");
  scanf("%d", &dimension);
  while(!(startDirection == 'l' || startDirection == 'u' || startDirection == 'r' || startDirection == 'd')) {
    printf("Enter the starting direction of the matrix (l - left, u - up, r - right, d - down): \n");
    scanf(" %c", &startDirection);
  }
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
  chosenMenuAction(menu());
}

void chosenMenuAction(char chosenMenuOption) {
  switch(chosenMenuOption)
  {
    case '1':
      userGuide();
      break;
    case '2':
      matrixGeneration();
      break;
    case '3':
      printf("Save\n");
      break;
    case '4':
      printf("Load\n");
      break;
    case '5':
      printf("Print\n");
      break;
    case '6':
      exit(0);
      break;
  }
}
