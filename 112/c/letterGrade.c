#include <stdio.h>

//By Sean Stahly
int main() {
  //get number of tests and quizes
  int numTests, numQuizes;
  float testTotal, quizTotal;
  printf("Please enter the number of test grades you will be entering.\n");
  scanf("%d", &numTests);
  printf("Please enter the number of quiz grades you will be entering.\n");
  scanf("%d", &numQuizes);

  int testCount = 0, quizCount = 0;

//get test scores
  while (testCount < numTests) {
    float testScore = 0;
    printf("Please enter the score of test %d as a percent.\n", (testCount +1));
    scanf("%f", &testScore);
    testTotal += testScore;
    testCount += 1;
  }

//get quiz scores
  while (quizCount < numQuizes) {
    float quizScore = 0;
    printf("Please enter the score of quiz %d as a percent.\n", (quizCount + 1));
    scanf("%f", &quizScore);
    quizTotal += quizScore;
    quizCount += 1;
  }

  //get average test grade
  float testGrade = testTotal / testCount;
  float quizGrade = quizTotal / quizCount;

  //compute final grade
  float totalGrade = (testGrade *.8) + (quizGrade * .2);
  printf("Your grade is %.2f. You have scored a", totalGrade);

  //output letter grade
  if (totalGrade >= 90.0) {
    printf("n A.\n");
  } else if (totalGrade >= 87.0) {
    printf(" B+.\n");
  } else if (totalGrade >= 80.0) {
    printf(" B.\n");
  } else if (totalGrade >= 77.0) {
    printf(" C+.\n");
  } else if (totalGrade >= 70.0) {
    printf(" C.\n");
  } else if (totalGrade >= 67.0) {
    printf(" D+.\n");
  } else if (totalGrade >= 60.0) {
    printf(" D.\n");
  } else {
    printf("n F.\n");
  }
}
