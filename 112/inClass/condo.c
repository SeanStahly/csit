//Created by Sean Stahly
#include <stdio.h>

float calculateMortgagePrice(float yearlyRate, int monthlyPaymentsNumber, float principle);

int main() {
  //set initial variables for both the condo bought now and later
  float nowPrice = 55000.00;
  float nowMortgage = .14;
  float futurePrice = 60000.0;
  float futureMortgage = .115;
  float downPayment = .2;

  //get starting price of condos
  float nowPayment = nowPrice * (1.0 - downPayment);
  float futurePayment = futurePrice * (1.0 - downPayment);

  //calculate mortgages
  float nowMortgageTotal = calculateMortgagePrice(nowMortgage, (30*12), nowPayment);
  float futureMortgageTotal = calculateMortgagePrice(futureMortgage, (30*12), futurePayment);

  //determine when to buy
  if (nowMortgageTotal < futureMortgageTotal) {
    printf("Mrs. X should buy now because it will cost her $%.2f comapred to $%.2f\n", nowMortgageTotal, futureMortgageTotal);
  } else {
    printf("Mrs. X should buy in a year because it will cost her $%.2f comapred to $%.2f\n", futureMortgageTotal, nowMortgageTotal);
  }
}

//formula taken from mortgage_calculator article on wikipedia
float calculateMortgagePrice(float yearlyRate, int monthlyPaymentsNumber, float principle) {
  float monthlyRate = yearlyRate/12;
  //1+r
  float positiveInterestRate = 1 + monthlyRate;

  //(1+r)^n
  float interestToPower = positiveInterestRate;
  for (int i = 1; i < monthlyPaymentsNumber; i++) {
    interestToPower *= positiveInterestRate;
  }

  //rP(1+r)^N
  float nominator = monthlyRate * principle * interestToPower;

  //(1+r) - 1
  float denominator =  interestToPower - 1;

  //(rP(1+r)^n) / ((1+r)^n - 1)
  float monthlyPaymentAmount = nominator/denominator;

  return monthlyPaymentAmount * monthlyPaymentsNumber;
}
