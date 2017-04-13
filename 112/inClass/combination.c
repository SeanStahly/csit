//By Sean Stahly

//get input from user of the total number and combination number within the group
//find factorial of total
//find factorial of combination number within the group
//find the factoral of (total - combination number) ---difference
//print data

#include <stdio.h>

//declared to avoid compiler running of implicit definition
int fact(int n);

int main() {
  int total, combination;

  //get inputs
  printf("Please enter the total number of objects: ");
  scanf("%d", &total);
  printf("Please enter the number of objects within the group: ");
  scanf("%d", &combination);

  int difference = total - combination;

  //find total factorial
  int totalCount = total;
  int totalFactorial = 1;
  while (totalCount > 1) {
    totalFactorial *= totalCount;
    totalCount--;
  }

  //find combination factorial
  int combinationCount = combination;
  int combinationFactorial = 1;
  while (combinationCount > 1) {
    combinationFactorial *= combinationCount;
    combinationCount--;
  }

  //find difference factorial
  int differenceCount = difference;
  int differenceFactorial = 1;
  while (differenceCount > 1) {
    differenceFactorial *= differenceCount;
    differenceCount--;
  }

  //get number of combinations
  // int combinations = totalFactorial / (combinationFactorial * differenceFactorial);
  int combinations = fact(total) / (fact(combination) * fact(difference));

  //printout results
  printf("For %d objects, you can have %d groups of %d objects.\n", total, combinations, combination);
}

//finds the factorial for a number n
int fact(int n) {
  if (n > 1)
    //continue recursion
    return n * fact(n-1);
  else
    //end recursion
    return 1;
}
