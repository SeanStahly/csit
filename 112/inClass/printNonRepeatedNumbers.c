#include <stdio.h>
#include <stdbool.h>

int main()
  int final[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  int nums[20] = {11, 12, 13, 14 ,15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 22, 23, 24, 25, 78};

  for (int i =0; i < 20; i++) {
    printf("Enter number %d: ", i+1);
    scanf("%d", nums[i]);
  }

  

}
