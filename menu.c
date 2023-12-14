#include <stdio.h>

void printMenu() {
  printf("\e[1;1H\e[2J"); // console clear regex
  printf(" ___________________________________________ \n");
  printf("|           Spiral Matrix Generator         |\n");
  printf("|                                           |\n");
  printf("|  #1 ~ User Guide                          |\n");
  printf("|  #2 ~ Matrix Generation                   |\n");
  printf("|  #3 ~ Save a matrix to a file             |\n");
  printf("|  #4 ~ Load a matrix from a file           |\n");
  printf("|  #5 ~ Print the current matrix            |\n");
  printf("|  #6 ~ Exit                                |\n");
  printf("|___________________________________________|\n");
}


char menu() {

  char menuOption = '0';
  printMenu();
  printf("> Choose an option (1-6): ");
  scanf(" %c", &menuOption);

  while(!(menuOption == '1' || menuOption == '2' || menuOption == '3' || menuOption == '4' || menuOption == '5' || menuOption == '6')) {
    printMenu();
    printf("  Invalid option!\n");
    printf("> Choose an option (1-6): ");
    scanf("%c", &menuOption);
  }

  return menuOption;
}

