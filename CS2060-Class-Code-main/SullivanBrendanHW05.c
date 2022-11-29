#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


void fgetsRemoveNewLine(char* charptr);
void adminSetUp(char* orgNamePtr, double* raceCostPtr, double* raceDistancePtr);
bool getValidDouble(double* test);
char getValidChar(char* SIZES[4]);


char* SIZES[4] = {"(s)mall", "(m)edium", "(l)arge", "(x)tra - large"};

int main(void) {
	

	//Declare a character array of size 80 called organizationName
	//Declare raceDistance as a double
	//Declare raceCost as a double
	//Call adminSetUp functionand pass the OrganizationName, bikeDistanceand bikeRegistrationCost
	//Display bike organization name, distanceand cost
	
	char organizationName[80] = {0};
	double raceDistance = 0;
	double raceCost = 0;
	adminSetUp(organizationName, &raceCost, &raceDistance);
	printf("%s  %lf  %lf", organizationName, raceCost, raceDistance);


	//Prompt for T-shirt//
	puts("Select your shirt size by entering the character in parenthesis: (s)mall (m)edium (l)arge  (x)tra-large.");
	getValidChar(SIZES);

}  //main



void adminSetUp(char* orgNamePtr, double* raceCostPtr, double* raceDistancePtr) {
	bool validCost, validDist = false;
	puts("Setup Mode\nEnter the organization name:\n");   //Get organization name
	fgetsRemoveNewLine(orgNamePtr);

	do {
		puts("\nEnter a number for the race cost:\n");   //Get valid Cost
		validCost = getValidDouble(raceCostPtr);
	} while (validCost != true);

	do {
		puts("\nEnter a number for the race distance:\n");   //Get valid Distance
		validDist = getValidDouble(raceDistancePtr);
	} while (validDist != true);

}


bool getValidDouble(double* test) {
	bool scannedVar = scanf("%lf", test);   //read in double
	while ((getchar()) != '\n');
	if (scannedVar == true) {
		return true;
	}
	else {
		return false;
	}
}


void fgetsRemoveNewLine(char* charptr) {
	fgets(charptr, 80, stdin);

	if (charptr[strlen(charptr) - 2] == '\n') {   //test second to last element
		charptr[strlen(charptr) - 2] = '\0';
	}
	else if (charptr[strlen(charptr) - 1] == '\n') {   //test for last element
		charptr[strlen(charptr) - 1] = '\0';
	}

}   //fgetsnewline


char getValidChar(char* SIZES[4]) {
	char size = 'a';
	bool validSize = false;
	do {

		scanf("%c", &size);   //read in char
		size = tolower(size);   //convert to lowercase
		
	
		for (int i = 0; i < strlen(*SIZES); i++) {   //search the sizes array for the char that user entered
			if (size == SIZES[i][1]) {
				validSize = true;   //if there is a match, move on
			}
		}
		if (validSize == false) {
			puts("Error. Please enter a valid shirt size");
		}
		
	} while (validSize == false);
	
	return size;
}