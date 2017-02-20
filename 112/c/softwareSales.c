#include <stdio.h>

//by Sean Stahly
int main() {
  int packageSales;
  float discount = 0.0;

  //receive number of packages from the use
  printf("Please enter the number of packages that you will purchase.\n");
  scanf("%d", &packageSales);

  float grossPrice  = 99.0 * packageSales;

  //calculate discount
  if(packageSales >= 100) {
    discount = grossPrice * .5;
  } else if (packageSales >= 50) {
    discount = grossPrice * .4;
  } else if (packageSales >= 20) {
    discount = grossPrice * .3;
  } else if (packageSales >= 10) {
    discount = grossPrice * .2;
  }

  float total = grossPrice - discount;

  printf("You will receive a discount of $%.2f.\n", discount);
  printf("It will cost you $%.2f to purchase the softtware.\n", total);
}
