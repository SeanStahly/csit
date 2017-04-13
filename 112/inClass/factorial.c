//by Sean Stahly
//I implemented this thorugh both a loop (with algorithm)
//and a recursive function

//input a number
//set a total equal to that number
//set count = number - 1
//start a while
  //while count > 1
  //total = multiply by count
  // count --
//print number and factorial(total)

#include<stdio.h>

//declare method before it is used
int fact(int n);

int main() {
  //declare variables
  int num, total, count;

  //get input
  printf("Please enter a number: ");
  scanf("%d", &num);

  //set initial variables for total and count
  total = num;
  count = num - 1;

  while (count > 1) {
    total *= count;
    count--;
  }

  printf("The factorial for %d is %d.\n",num,total);
  printf("The factorial for %d is %d using the recursive factorial method.\n",num,fact(num));
}

int fact(int n) {
  if (n > 1)
    //continue recursion
    return n * fact(n-1);
  else
    //end recursion
    return 1;
}
