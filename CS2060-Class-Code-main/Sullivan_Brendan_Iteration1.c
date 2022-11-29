#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Org {  //change to org
	char orgName[90];
	double raceDistance;
	double raceCost;
	double jerseyCost;
	double charityPerc;
	double totalRiders;
	double raceSales;
	double jerseySales;
	double totalJerseys;
}Org;

typedef struct Racer {
	char name;
	Org orgOfRace;
	char jerseySize;
	bool wantJersey;
}Racer;

bool adminSetUp(Org* orgPtr);
bool loginTest(void);
bool bikeRegistration(Org* orgPtr, Racer* racerPtr);
void displayRaceInfo(Org* orgPtr);
void displaySummary(Org* orgPtr);
void jerseySelection(Org* orgPtr, Racer* racerPtr);
void takePayment(Org* orgPtr, Racer* racerPtr);
bool testCreditCard(char card[]);
void fgetsRemoveNewLine(char* charptr);
bool getValidDouble(int max, int min, double* value);
char getValidChar(const char* array[]);


const char* SIZES[4] = {"(s)mall", "(m)edium", "(l)arge", "(x)tra - large"};
#define SIZES_LENGTH 4
#define YN_LENGTH
#define PASSCODE "B!k34u"
#define MAX_MILES 200
#define MIN_MILES 1
#define MAX_RIDE_COST 250
#define MIN_RIDE_COST 50
#define MAX_JERSEY_COST 150
#define MIN_JERSEY_COST 50
#define MIN_CHARITY 5
#define MAX_CHARITY 30
#define LOGIN_ATTEMPTS 3
const char* YN[] = { "(y)es", "(n)o"};

int main(void) {


	//Declare a character array of size 80 called organizationName
	//Declare raceDistance as a double
	//Declare raceCost as a double
	//Call adminSetUp functionand pass the OrganizationName, bikeDistanceand bikeRegistrationCost
	//Display bike organization name, distance and cost


	Org org = { 0 };
	Org* orgPtr = &org;
	bool adminSuccess = adminSetUp(orgPtr);   //call admin setup
	bool registSuccess = false;
	if (adminSuccess == true) {
		do {
			Racer racer = { 0 };
			registSuccess = bikeRegistration(orgPtr, &racer);
		} while (registSuccess == true);


	}
	
}  //main



bool adminSetUp(Org* orgPtr) {
	bool success = false;
	if (loginTest() == true) {
		bool validCost, validDist, validPerc, validJerseyCost = false;
		puts("Setup Mode\nEnter the organization name:");   //Get organization name
		fgetsRemoveNewLine(orgPtr->orgName);

		do {
			printf("Enter the cost of the race between %d and %d:", MAX_RIDE_COST, MIN_RIDE_COST);   //Get valid Cost
			validCost = getValidDouble(MAX_RIDE_COST, MIN_RIDE_COST, &orgPtr->raceCost);
		} while (validCost != true);

		do {
			printf("Enter the cost of a jersey between %d and %d:", MAX_JERSEY_COST, MIN_JERSEY_COST);   //Get valid jersey Cost
			validJerseyCost = getValidDouble(MAX_JERSEY_COST, MIN_JERSEY_COST, &orgPtr->jerseyCost);
		} while (validJerseyCost != true);

		do {
			printf("Enter the distance of the race in miles between %d and %d:", MAX_MILES, MIN_MILES);   //Get valid Distance
			validDist = getValidDouble(MAX_MILES,MIN_MILES, &orgPtr->raceDistance);
		} while (validDist != true);

		do {
			printf("Enter the percentage of sales to be donated to charity between %d and %d:", MAX_CHARITY, MIN_CHARITY);   //get charity %
			validPerc = getValidDouble(MAX_CHARITY, MIN_CHARITY, &orgPtr->charityPerc);
		} while (validPerc != true);
		success = true;
	}

	return success;
	
}//adminSetup


bool loginTest(void) {
	char attempt[80] = { 0 };
	bool success = false;
	for (int i = 0; i < LOGIN_ATTEMPTS; i++) {
		if (success == false) {
			printf("Enter the passcode. You have %d attempts remaining\n", LOGIN_ATTEMPTS - i);
			fgetsRemoveNewLine(attempt);
			if ((strcmp(attempt, PASSCODE)) == 0) {
				success = true;
			}
		}
	}
	
		return success;
}//loginTest


bool bikeRegistration(Org* orgPtr, Racer* racerPtr) {
	bool contin = true;
	displayRaceInfo(orgPtr);   //display race info

	char racerName[80] = { 0 };
	char* racerNamePtr = &racerName[80];
	puts("\nPlease enter your name:");
	fgetsRemoveNewLine(racerNamePtr);  //get name of racer & test for "quit"

	if ((strcmp(racerName, "Quit")) == 0) {
		if (loginTest() == true) {
			displaySummary(orgPtr);
			contin = false;
		}
	}
	else if ((strcmp(racerName, "quit")) == 0) {
		if (loginTest() == true) {
			displaySummary(orgPtr);
			contin = false;
		}
	}
	else if ((strcmp(racerName, "QUIT")) == 0) {
		if (loginTest() == true) {
			displaySummary(orgPtr);
			contin = false;
		}
	}
	else {
		racerPtr->wantJersey = false;
		jerseySelection(orgPtr, racerPtr);   //prompt for jersey
		takePayment(orgPtr, racerPtr);   //
		puts("Do you want a receipt(y)es or (n)o ? ");
		if ((getValidChar(YN) == 'y') || (getValidChar(YN) == 'Y')) {
			printf("Race: $%-10.2lf\nJersey: $%-10.2lf\n\n", orgPtr->raceCost, orgPtr->jerseyCost);
			double totalCost = orgPtr->raceCost + orgPtr->jerseyCost;
			double dono = totalCost * orgPtr->charityPerc * 0.01;
			printf("Total Cost: $%10.2lf\nDonation to Charity: $%10.2lf", totalCost, dono);

		}
	}

	return contin;
}//bikeRegistration


void displayRaceInfo(Org* orgPtr) {
	printf("\n\nYou can register for one of the following races and %2.0lf percent will be raised for %s", orgPtr->charityPerc, orgPtr->orgName);
	printf("\n%-10s%-10s%-10s", "Ride", "Distance", "Cost");
	printf("\n%-10.0d%-2.0lf miles $%-10.0lf", 1, orgPtr->raceDistance, orgPtr->raceCost);
	printf("\nYou will have the option to purchase a jersey for $%2.0lf", orgPtr->jerseyCost);

}//displayRaceInfo


void displaySummary(Org* orgPtr) {
	printf("");

}//displaySummary


void jerseySelection(Org* orgPtr, Racer* racerPtr) {
	if ((getValidChar(YN) == 'y') || (getValidChar(YN) == 'Y')) {
		racerPtr->jerseySize = getValidChar(SIZES);   //store jersey size
		orgPtr->jerseySales += orgPtr->jerseyCost;   //add up jersey sales
		racerPtr->wantJersey = true;
	}

}//jerseySelection


void takePayment(Org* orgPtr, Racer* racerPtr) {
	double totalCost = orgPtr->raceCost;
	printf("\nCost of race: $%-10.2lf", orgPtr->raceCost);
	if (racerPtr->wantJersey == true) {
		printf("\nCost of jersey: $%-10.2lf", orgPtr->jerseyCost);
		totalCost += orgPtr->jerseyCost;
	}
	printf("\n\nYour total is $%-10.2lf", totalCost);

	char cardNum[80] = { 0 };
	char* cardNumPtr = &cardNum[80];

	puts("\n\nPlease enter you credit card number with no spaces or dashes:");   //get card info
	fgetsRemoveNewLine(cardNumPtr);
	bool cardSuccess = false;
	do {
		cardSuccess = testCreditCard(cardNum);
		if (cardSuccess == false) {
			puts("\nError. Try Again.\n");
		}
	} while (cardSuccess == false);

}//takePayment


bool testCreditCard(char card[]) {
	bool success = true;
	if ((strlen(card)) != 13){
		puts("Error. Value entered was not the correct length, try again.");
		success = false;
	}
	else {
		int j = 0;
		char characters[4] = { 0 };
		char digits[9] = { 0 };

		for (int i = 0; i < 13; i++) {
			if (i < 4) {
				characters[i] = toupper(card[i]);
			}
			else {
				digits[j] = card[i];
				j++;
			}
		}

		for (int i = 0; i < 4; i++) {
			if ((characters[i] > 90) || (characters[i] < 65)) {    //test the first 4 chars for letters
				puts("Error. Try Again");
				success = false;
			}
		}

		for (int i = 0; i < 9; i++) {
			if ((digits[i] > 57) || (digits[i] < 48)) {
				puts("Error. Try Again");
				success = false;
			}
		}
	}

	return success;
}//testCreditCard


bool getValidDouble(int max, int min, double* value) {

	bool success = false;
	char tempChar[3] = { 0 };   //initial string to read in input
	char* buff;
	fgetsRemoveNewLine(tempChar);   //read in string

	*value = strtod(tempChar, &buff);   //convert string to double

	if ((*value >= min) && (*value<=max)){   //range check
		success = true;
	}
	else {
		puts("Error, try again");
	}
	return success;
	
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


char getValidChar(const char* array[]) {
	//printf("%c", array[0][1]);
	//printf("%c\n", array[1][1]);
	//printf("%c", SIZES[0][1]);
	//printf("%c", SIZES[1][1]);

	bool match = false;
	char input = 0;
	do {

		input = getchar();   //read in char
		input = tolower(input);   //convert to lowercase
		int i = 0;

		while (array[i] != NULL) {   //search the  array for the char that user entered
			if (input == array[i][1]) {
				match = true;   //if there is a match, move on
			}
			i++;
		}
		if (match == false) {
			puts("Error. Please enter a valid shirt size");
		}

	} while (match == false);

	return input;
}