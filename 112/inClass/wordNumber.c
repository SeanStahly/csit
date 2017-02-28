//by Sean Stahly
//enter the number -num
//get the digits of the number
  // firstDigit = num / 10
  // secondDigit = num % 10
// if and else ifs comparing firstDigit, out put number's - outputWord
// if and else ifs comparing secondDigit, out put number's word - +=outputWord
//print output

# include <stdio.h>
# include <string.h>

int main() {
  int num;
  char numWord[20];

  //get info
  printf("Please enter a number: ");
  scanf("%d", &num);

  //get value of digits in the tens and one place respectively;
  int firstDigit = num / 10;
  int secondDigit = num % 10;

  //get word for the tens digit
  if (firstDigit == 2) {
    strcpy(numWord, "twenty");
  } else if (firstDigit == 3) {
    strcpy(numWord, "thirty");
  } else if (firstDigit == 4) {
    strcpy(numWord, "fourty");
  } else if (firstDigit == 5) {
    strcpy(numWord, "fifty");
  } else if (firstDigit == 6) {
    strcpy(numWord, "sixty");
  } else if (firstDigit == 7) {
    strcpy(numWord, "seventy");
  } else if (firstDigit == 8) {
    strcpy(numWord, "eighty");
  } else if (firstDigit == 9) {
    strcpy(numWord, "ninety");
  }

  //get word for the ones digit
  if (secondDigit == 1) {
    strcat(numWord,"-one");
  } else if (secondDigit == 2) {
    strcat(numWord,"-two");
  } else if (secondDigit == 3) {
    strcat(numWord,"-three");
  } else if (secondDigit == 4) {
    strcat(numWord,"-four");
  } else if (secondDigit == 5) {
    strcat(numWord,"-five");
  } else if (secondDigit == 6) {
    strcat(numWord,"-six");
  } else if (secondDigit == 7) {
    strcat(numWord,"-seven");
  } else if (secondDigit == 8) {
    strcat(numWord,"-eight");
  } else if (secondDigit == 9) {
    strcat(numWord,"-nine");
  }

  //print output
  printf("The number is %d, the word is %s.\n", num, numWord);
}
