//declare arrays to hold used values and input numbers
//loop through input
  //if input number is not in unsigned
    //add to used
    //print out number
  //if number in used
    //move to next number

#include <stdio.h>
#include <stdbool.h>

int main() {
  int final[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int nums[20] = {11, 12, 13, 14 ,15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 22, 23, 24, 25, 78};

  //get number inputs
  for (int i =0; i < 20; i++) {
    printf("Enter number %d: ", i+1);
    scanf("%d", nums[i]);
  }

  //check every number in input
  for (int i = 0; i < 20; i++) {
    int num = nums[i];
    int flag = 1;
    int index =0;

    //check if the number was used already
    for (int j = 0; j < 20; j++) {
      if (final[j] == num) {
        flag = 0;
        break;
      }
    }

    //if number not used, add it to 'used' array and print it out
    if (flag == 1 ) {
      final[i] = num;
      //dess this need to be sorted? if not un comment this line
      printf("%d ", num);
    }
  }


  printf("\n");
}
