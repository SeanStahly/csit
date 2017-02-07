#include <stdio.h>
//created By Sean Stahly 1/31/17

int main() {
  float hours, wage, state, fed, ss, grossPay;

  printf("Please enter the hours worked.\n");
  scanf("%f", &hours);
  printf("Please enter your wage.\n");
  scanf("%f", &wage);
  printf("Please enter the state tax rate.\n");
  scanf("%f", &state);
  printf("Please enter the federal tax rate.\n");
  scanf("%f", &fed);
  printf("Please enter the social security rate.\n");
  scanf("%f", &ss);

  if (hours > 40) {
    float overtime = (hours - 40) * wage * 1.5;
    grossPay = (40 * wage) + overtime;
  } else {
    grossPay = hours * wage;
  }

  float stateFee, fedFee, ssFee;
  stateFee = grossPay * state;
  fedFee = grossPay * fed;
  ssFee = grossPay * ss;

  float total = grossPay - stateFee - fedFee - ssFee;

  printf("Your gross pay is %.2f.\n", grossPay);
  printf("Your total pay is %.2f.\n", total);

  return 0
}
