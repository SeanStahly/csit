//initilize array
//ask the user to enter digits
//loop through array to see if item is found within the array

#include<stdio.h>
#include<string.h>

void loopThrough(int n, int arr[], int size) {
  //initializ output
  char out[18] = "Sorry, not found.\n";

  //loop through array size
  for ( int i = 0; i < size; i++) {
    //check if n is in the aray
    if (arr[i] == n)
      strcpy(out, "Found it!\n");
  }

  //print result
  printf("%s", out);
}

int main() {
  int arr[8] = {25, 19, 3, 54, 42, 17, 61, 7};

  int in;

  for (int i =0; i < 2; i ++) {
    printf("please enter a number: ");
    scanf("%d", &in);
    loopThrough(in, arr, (sizeof(arr)/sizeof(arr[0])));
  }
}
