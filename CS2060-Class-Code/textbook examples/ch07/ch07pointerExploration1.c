/*******************
 Understanding pointers

 Add comments to explain the code
**************/

#include <stdio.h>


int main ()
{
	// Initalize houseNum
	int houseNum = 13;
	int calcHouseNum1 = 0;
	int calcHouseNum2 = 0;
	int *houseNumPtr = &houseNum;
	
	printf("houseNum %d\n", houseNum);   //prints the value of houseNum: 13

	printf("&houseNum %p\n\n", &houseNum);   //prints the address that houseNum is stored at

	printf ("*houseNumPtr  %d\n", *houseNumPtr);   //prints the data that is stored at the address of houseNum

	printf ("houseNumPtr %p\n\n", houseNumPtr);   //prints the address that houseNum is stored at

	printf ("&houseNumPtr %p\n\n", &houseNumPtr);   //prints the address that the pointer for houseNum is stored at

	calcHouseNum1 =  *houseNumPtr + *houseNumPtr;

	printf("*houseNumPtr + *houseNumPtr is %d\n\n", calcHouseNum1);   //prints 13 plus 13: 26

	calcHouseNum2 = 2 * (*houseNumPtr);

	printf("2 * (*houseNumPtr) is %d\n\n", calcHouseNum2);   //prints out 13 * 2: 26

	printf("\n&*houseNumPtr = %p"
		"\n*&houseNumPtr = %p\n", &*houseNumPtr, *&houseNumPtr);   //both print out the address of houseNum
			
	return 0;
}
