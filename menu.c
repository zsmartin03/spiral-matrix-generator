#include <stdio.h>

void printMenu() {
  printf("\e[1;1H\e[2J"); // console clear regex
  printf(" ___________________________________________ \n");
  printf("|                                           |\n");
  printf("|           Spiral Matrix Generator         |\n");
  printf("|                                           |\n");
  printf("|  #1 ~ User Guide                          |\n");
  printf("|  #2 ~ Matrix Generation                   |\n");
  printf("|  #3 ~ Save a matrix to a file             |\n");
  printf("|  #4 ~ Load a matrix from a file           |\n");
  printf("|  #5 ~ Print the current matrix            |\n");
  printf("|  #6 ~ Exit                                |\n");
  printf("|                                           |\n");
  printf("|___________________________________________|\n");
}


int menu() {

  int menuOption = 0;
  printMenu();
  
  do {
    printf("\n > Choose an option (1-6): ");
    if(scanf(" %d", &menuOption) != 1) {
      printMenu();
      printf("\n   Invalid option, enter an integer!\n");
      int c;
      while ((c = getchar()) != '\n' && c != EOF);

    }
    else if(!(menuOption == 1 || menuOption == 2 || menuOption == 3 || menuOption == 4 || menuOption == 5 || menuOption == 6)) {
      printMenu();
      printf("\n   Invalid option, enter a number between 1 and 6!\n");
    }
  } while(!(menuOption == 1 || menuOption == 2 || menuOption == 3 || menuOption == 4 || menuOption == 5 || menuOption == 6));

  return menuOption;
}

