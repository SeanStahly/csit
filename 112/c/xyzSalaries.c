#include <stdio.h>

//By Sean Stahky
//This program assumes data is entered correctly
int main() {
  int jobCode, eduCode, meritRating, years;
  float finalPay = 100.0;

  //receive data input
  printf("Please enter the employee's job classification: ");
  scanf("%d", &jobCode);
  printf("Please enter the employee's education code: ");
  scanf("%d", &eduCode);
  printf("Please enter the employee's merit rating code: ");
  scanf("%d", &meritRating);
  printf("Please enter the employee's years of service: ");
  scanf("%d", &years);

  //don't need to check for 1 because it adds 0
  if (jobCode == 2) {
    finalPay += 5;
  } else if (jobCode == 3) {
    finalPay += 15;
  } else if (jobCode == 4) {
    finalPay += 25;
  } else if (jobCode == 5) {
    finalPay += 50;
  }

  //don't need to check for 1 because it adds 0
  if (eduCode == 2) {
    finalPay += 10;
  } else if (eduCode == 3) {
    finalPay += 25;
  } else if (eduCode == 4) {
    finalPay += 50;
  } else if (eduCode == 5) {
    finalPay += 15;
  }

  //don't need to check for 1 because it adds 0
  if (meritRating == 1) {
    finalPay += 10;
  } else if (meritRating == 2) {
    finalPay += 25;
  }

  //add year percentage
  if (years > 10) {
    finalPay += 5;
    finalPay += (4 * (years - 10));
  } else {
    finalPay += 5;
  }

  printf("\nThe employee's pay is %.2f of the base pay.\n", finalPay);

}
