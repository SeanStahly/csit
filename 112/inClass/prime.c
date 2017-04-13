//By Sean Stahly
#include <stdio.h>

//will print out the prime numbers between start and end
void longCurrentMethod(int start, int end) {
  //even numbers can't be prime
  if (start % 2 ==0)
    start++;
  //check every odd number between start and end
  for (int i = start; i < end; i+=2) {
    int prime = 1;
    //check numbers between 3 and n to see if they divide evenly into i
    for (int j = 3; j < i; j +=2) {
      if (i%j == 0) {
        prime = 0;
        break;
      }
    }
    if (prime == 1) {
      printf("%d, ", i);
    }
  }
}

//this will ask the user to enter numbers and will then print out the prime numbers between the entered numbers
int main() {
  int start, end;
  printf("Please insert a start number: ");
  scanf("%d", &start);
  printf("Please insert an end number: ");
  scanf("%d", &end);

  longCurrentMethod(start, end);
}
