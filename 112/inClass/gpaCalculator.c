#include <stdio.h>

int main() {
  float test1, test2, test3;
  printf("Please enter the first test score.\n");
  scanf("%f", &test1);
  printf("Please enter the second test score.\n");
  scanf("%f", &test2);
  printf("Please enter the third test score.\n");
  scanf("%f", &test3);

  float total = test1 + test2 + test3;
  float gpa = total / 3;

  printf("Your test average is %.2f\n", gpa);

  if (gpa >= 70.00) {
    printf("Congratulations! You received a passing grade!\n");
  } else {
    printf("Sorry. You did not receive a passing grade.\n");
  }

  return 0;
}
