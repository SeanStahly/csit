//By Sean Stahly

//For this program, read can be substituted by "entered" or "ask the user for"
//1. read current date
//2. prep output header
//3. read number of items
//4. begin loop for number of items
  //4a. read item
    //4a1. read item number
    //4a1. read date last sold
    //4a1. read number of items available
    //4a1. read cost per item
    //4a1. read regular sell price
  //4b. calculate sale price
    //4b1. ensure that there is more than 1 item left
    //4b2. get number of days last sold
    //4b3. calculate sale price
    //4b4. ensure sale price is above or equal to the cost
  //4c. output data
//terminate program

#include <stdio.h>
#include <string.h>

//calculate the days elasped since the last sale
int calculateDaysSinceLastSale(int currentDate, int lastSaleDate) {
  //get the days since beginning of year
  int currentDays = currentDate%1000;
  int lastDays = lastSaleDate%1000;

  //get the year
  int currentYear = currentDate/1000;
  int lastYear = lastSaleDate/1000;

  //used incase the last date sold was in the 90s, this program only works from 1918 on
  if (lastYear > 17) {
    currentYear += 100;
  }

  //add 365 days to current days per year difference
  if (currentYear > lastYear) {
    currentDays += (365 * (currentYear - lastYear));
  }

  //return difference in days since the last sale
  return currentDays - lastSaleDate;
}

//claculate the sale price of an item
float getSalePriceOfItem(int daysSinceLastSold, int numberInStock, float cost, float regularPrice) {
  float salePrice = cost;
  //ensure item is not the last one in stock
  if(numberInStock != 1) {

    //calculate discount
    if (daysSinceLastSold > 90) {
      salePrice *= 0.6;
    } else if (daysSinceLastSold > 60) {
      salePrice *= .8;
    } else if(daysSinceLastSold > 30) {
      salePrice *= .9;
    }

    //don't sell for less than cost
    if (salePrice <  cost) {
      salePrice = cost;
    }
  }

  return salePrice;
}

int main() {
  //get number of items to be scanned
  int numberOfItems, currentDate;
  printf("Enter the number of items to be scanned: ");
  scanf("%d", &numberOfItems);

  //getCurrentDate
  printf("Please enter the current date: ");
  scanf("%d", &currentDate);

  //initialize output
  int charLength = 65 * numberOfItems;
  char output[charLength];

  strcpy(output, "ITEM   LAST SALE     DAYS    NO. IN    COST    REG.     SALE\n");
  strcat(output, " NO.     DATE      ELAPSED    STOCK           PRICE    PRICE\n");

  //process an item
  for (int i =0; i < numberOfItems; i++) {
    //intialize read variables
    int itemNumber, lastDateSold, stock;
    float cost, regPrice;

    //read informations
    printf("Please enter the item number for item %d: ",(i+1));
    scanf("%d", &itemNumber);
    printf("Please enter the the last date item %d was sold: ",(i+1));
    scanf("%d", &lastDateSold);
    printf("Please enter the stock of item %d: ",(i+1));
    scanf("%d", &stock);
    printf("Please enter the cost per item %d: ",(i+1));
    scanf("%f", &cost);
    printf("Please enter the regular price for item %d: ",(i+1));
    scanf("%f", &regPrice);

    //get last date sold and days Elapsed`
    int lastSaleDate = lastDateSold%1000;
    int daysElapsed = calculateDaysSinceLastSale(currentDate, lastDateSold);
    float salePrice =  getSalePriceOfItem(daysElapsed, stock, cost, regPrice);

    strcat(output, ("%3d       %3d        %3d        %2d    %2.2f   %2.2f    %2.2f\n", itemNumber, lastSaleDate, daysElapsed, stock, cost, regPrice, salePrice));
  }

  printf("%s", output);
}
