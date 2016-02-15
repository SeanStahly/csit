#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void pointerPrint(char ** argv);
char ** parse(char * c);
int main(int argc, char ** argv, char ** envp)
{
	char * String = malloc(100);
	scanf("%99[^\n]s", String);
	char ** res = parse(String);
	pointerPrint(res);
	return 0;
}
char ** parse(char * c)
{

//	In class example VVVVVVVVVVVV
//	char cat[] = "Galaxy Cat";

//	char *ted = cat;
//	puts(ted);
//	ted++;
//	puts(ted);
//	ted++;
//	puts(ted);
//	ted++;	
//	Class example left above

	char ** result;
	//TODO add code here!!
	
	//Cool Stuff starts here :)
	//Determine Free antivirus... why Avast, why did you distract me... leaving the comment for amusement
	//Determine the number of pointers
	printf("String = '%s'\n", c);
	int pointers = 0;
	char *cfp = c;
	for( int i =0;  i < strlen(c); i++) {
		if(cfp[i] == ' ') {
			pointers++;
		}
	}
	
	//add 2 to pointers for  first and null pointer
	pointers+=2;
	printf("Number of pointers = %i\n", pointers);

	//size of array of pointers
	result = malloc(pointers * sizeof(int *));

	//get string to insert into arrays
	char *letters = c;

	for (int i = 0; i < pointers; i++) {
		//determine word  malloc size
		int a =0;
		while(letters[a] != ' ' && letters[a] != 0) {
			a++;
		}
		//allocate memory for each "word"
		result[i] = malloc(a+1);
		//insert word into memory
		int count = 0;
		while (letters[0] != ' ' && letters[0] != 0) {
			result[i][count] = letters[0];
			//move string one letter, galaxy cat0 -> alaxy cat0
			letters++;
			count++;
		} 
		//end a word
		result[i][count] = 0;
		//move letter past a space
		letters++;
	}
	//NULL after the words, represent the end of Array
	result[pointers -1] = NULL;
	
	//My code is above, Now less fun, but probably more functional code begins ....
	//Red lantern Hate kitties > regular galaxy cats
	return result;
}
void pointerPrint(char ** argv)
{
	printf("Address %p\n", &argv);
	for(int i=0; argv[i] != NULL; i++)
	{
		printf("Base[%d] Address %p PointerValue %p String=%s\n", i, &argv[i], argv[i], argv[i]);
	}
}
