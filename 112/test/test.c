#include <stdio.h>

int main() {
	int k[15];
	for (int i = 0; i < 15; i++)
		k[i] = 0;

	for(int i = 1; i <= 10; i++)
		k[i] = i;

	for(int i = 0; i < 15; i ++)
		printf("k[%d] = is %d\n", i, k[i]);
}
