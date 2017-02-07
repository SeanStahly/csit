#include <stdio.h>

int main() {
  //create variables
  int stockPurchased, stockSold;
  float pricePaid, priceSold, buyCommission, sellCommission;

  //enter variables
  printf("Please enter the number of shares Joe purchased.\n");
  scanf("%d", &stockPurchased);
  printf("Please enter the price per share of the stock Joe bought.\n$");
  scanf("%f", &pricePaid);
  printf("Please enter the stockbroker's buying commision percentage.\n");
  scanf("%f", &buyCommission);
  printf("Please enter the number of shares Joe sold.\n");
  scanf("%d", &stockSold);
  printf("Please enter the price per share of the stock Joe sold.\n$");
  scanf("%f", &priceSold);
  printf("Please enter the stockbroker's selling commision percentage.\n");
  scanf("%f", &sellCommission);

  //calculate gross Purchase amount
  float grossPurchase = stockPurchased * pricePaid;
  printf("Joe paid $%.2f for the stock.\n", grossPurchase);


  float commissionForBuying = grossPurchase * buyCommission / 100;
  printf("Joe paid his broker $%.2f when he bought the stock.\n", commissionForBuying);

  float grossProfit = stockSold * priceSold;
  printf("Joe sold the stock for $%.2f.\n", grossProfit);

  float commissionForSelling = grossProfit * sellCommission / 100;
  printf("Joe paid his broker $%.2f when he sold the stock.\n", commissionForSelling);

  float profit = grossProfit - grossPurchase - commissionForBuying - commissionForSelling;
  printf("Joe made a profit of %.2f dollars!\n", profit);
}
