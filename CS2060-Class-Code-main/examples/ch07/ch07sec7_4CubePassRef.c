// Passing Primitive Data Types and pointers
//Add comments to explain the code

#include <stdio.h>	
#include <stdlib.h>

int cubePass1(int number);
int cubePass2(int * numberPtr);

int main(void) {

	int numberMain = 5;
	int result = 0;
	
	printf ("In main before cubePass1  numberMain = %d\n", numberMain);	  //prints numberMain (5)
	printf("&numberMain = %p\n", &numberMain);   //Prints the address of numberMain
	result = cubePass1(numberMain);   //Pass by value
	printf ("In main after cubePass1  numberMain = %d\n", numberMain);   //prints numberMain (5)
	printf ("Result = %d\n", result);   //Prints the result of the function (125)
	printf("\nIn main before cubePass2  numberMain = %d\n", numberMain);   //prints numberMain (5)
	result = cubePass2(&numberMain);   //pass by reference
	printf("\nIn main after cubePass2  numberMain = %d\n", numberMain);   //prints numberMain (125)
	printf("result = %d\n", result);   //prints result of function (125)

} // main


int cubePass1 (int number)    //pass by value
{
	int cube = 0;
	puts("\nIn cubePass1");
	printf("number = %d\n", number);
	printf("&number = %p\n", &number);
	cube = number * number * number;
	printf("cube  = %d\n", cube);
	number = cube;   //does not change numberMain
	printf("number = %d\n", number);
	return cube;
} 

int cubePass2 (int * numberPtr)    //pass by reference
{
	int cube = 0;
	puts ("\nIn cubePass2");
	printf("numberPtr = %p\n", numberPtr);
	printf ("*numberPtr = %d\n", *numberPtr);
	printf("&numberPtr = %p\n", &numberPtr);
	cube = (* numberPtr )* (* numberPtr )* (* numberPtr); 
	*numberPtr = cube;   //changes numberMain to 125
	printf ("*numberPtr = %d\n", *numberPtr);
	return cube;
} 


