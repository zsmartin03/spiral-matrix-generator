#include <stdio.h>

int menu() {

  int menuOption = 0;
  
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

  return 1;
}

int main() {

  if(menu() == 1) {
    printf("kys");
  }

  return 0;
}

