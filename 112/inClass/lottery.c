#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//This function will have the user input a number
int getUserInput(int i) {
  int input;
  printf("Please enter number %d: ", i);
  scanf("%d", &input);
  return input;
}

int main() {
  //seed random with the time so it is more random
  srand(time(NULL));

  int lotto[5];
  int selec[5];

  int boolFlag = 1;
  //generate lotto, have the user input selec, and compare the numbers
  for(int i =0; i < 5; i++) {
    //get user input and store in array
    selec[i] = getUserInput(i);

    //generate lotto
    lotto[i] = (rand()%9)+1;

    printf("Your random number is: %d", lotto[i]);
    if (selec[i] != lotto[i]) {
      boolFlag = 0;
    }
  }

  //output results
  if(boolFlag == 1) {
    printf("Congrats! you won the lottery.");
  } else {
    printf("Too bad, you lost the lottery.");
  }
}
