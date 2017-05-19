#include <stdio.h>

// void printResults(int ids[], int arr[][]) {
//
// }

int main() {
  int ids[5] = {111, 222, 333, 444, 555};
  //federal tax 12%, state tax 8%
  //hours, wage, grosspay, federal tax, state tax, total deduction, netpay
  double info[5][7] = {
    {23.5, 12.50},
    {47.0, 18.75},
    {35.0, 21.0},
    {16.25, 28.0},
    {40.0, 32.0}
  };

  for(int i = 0; i < 5; i++) {
    //gross pay
    info[i][2] = info[i][0] * info[i][1];
    //federal tax
    info[i][3] = info[i][2] * 0.12;
    //state tax
    info[i][4] = info[i][2] * 0.08;
    //total deduction
    info[i][5] = info[i][3] + info[i][4];
    //netpay
    info[i][6] = info[i][2] - info[i][5];
  }

  // printResults(ids, info);

  printf(" ID    Hours    Wages    G. Pay    Fed. Tax    Sta. Tax    Deducted    Total\n");
  for (int i =0; i < 5; i++) {
    printf("%d    %.2f    %.2f    %.2f     %.2f       %.2f      %.2f       %.2f\n", ids[i], info[i][0], info[i][1], info[i][2], info[i][3], info[i][4], info[i][5], info[i][6]);
  }

  //add 2.50  to 333's wage

  printf("\n");
  for(int i =0; i < 5; i++) {
    if (ids[i] == 333) {
      info[i][1] = info[i][1] + 2.50;
      //gross pay
      info[i][2] = info[i][0] * info[i][1];
      //federal tax
      info[i][3] = info[i][2] * 0.12;
      //state tax
      info[i][4] = info[i][2] * 0.08;
      //total deduction
      info[i][5] = info[i][3] + info[i][4];
      //netpay
      info[i][6] = info[i][2] - info[i][5];
      break;
    }
  }

  printf(" ID    Hours    Wages    G. Pay    Fed. Tax    Sta. Tax    Deducted      Total\n");
  for (int i =0; i < 5; i++) {
    printf("%d    %.2f    %.2f   %7.2f     %6.2f      %6.2f      %6.2f     %7.2f\n", ids[i], info[i][0], info[i][1], info[i][2], info[i][3], info[i][4], info[i][5], info[i][6]);
  }
}
