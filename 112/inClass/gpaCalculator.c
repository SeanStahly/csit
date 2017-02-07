#include <stdio.h>

int main() {

  int count = 0;
  while (count < 5) {
    char name[20];
    printf("Please enter the name of the student.\n");
    scanf("%s", name);

    float total = 0;
    int testCount =1;

    while(testCount <= 3) {
      float testScore = 0;
      printf("Please enter the score for test %d.\n", testCount);
      scanf("%f", &testScore);
      total += testScore;
      testCount += 1;
    }

    float gpa = total / 3;

    printf("Your test average is %.2f\n", gpa);

    if (gpa >= 70.00) {
      printf("Congratulations %s! You received a passing grade!\n", name);
    } else {
      printf("Sorry %s. You did not receive a passing grade.\n", name);
    }
    count++;
  }

  return 0;
}
