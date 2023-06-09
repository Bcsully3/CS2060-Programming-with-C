///Author: Brendan Sullivan
///Class: CS 2060
/// Due date: 12/2/2022
/// Summary:
/// This program allows various organizations to set up a bike race fundraiser,
/// all inside the same system. They can control the parameters of their individual
/// organization's race, such as length, cost, the cost of a jersey, and more.
/// 
/// After the organizations have all set up their race fundraisers, it then allows
/// participants to register for one of the races by giving their name, jersey size
/// if they want a jersey, and their credit card info. Participants can register
/// until the escape key "quit" is entered for the participants name.
/// 
/// At that point, a summary is displayed for each organization, and an output file
/// is created/written to for each organization that hold their summary. The summary
/// include the amount raised, the number of participants, the number of jerseys sold, 
/// and more.





#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <float.h>

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
	double totalSales;
	double totalCharity;
}Org;

typedef struct Racer {
	char name[80];
	Org orgOfRace;
	char jerseySize;
	bool wantJersey;
	double payment;
}Racer;

typedef struct Node {
	Org org;
	struct Node* nextNode;
}Node;

bool adminSetUp(Org* orgPtr);
bool loginTest(void);
bool bikeRegistration(Node** headPtr, Racer* racerPtr);
double displayRaceInfo(Node** headPtr);
void displaySummary(Node** headPtr);
void jerseySelection(Org* orgPtr, Racer* racerPtr);
void takePayment(Org* orgPtr, Racer* racerPtr);
bool testCreditCard(char card[]);
void fgetsRemoveNewLine(char* charptr);
char getValidChar(const char* array[]);
bool validateDouble(const char* buff, double* validDblPtr, int max, int min);
bool compareString(const char str1[80], const char str2[80]);
bool insertNodes(Node** headPtr);
Org* chooseRace(Node** headPtr, double numberOfOrgs);


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
#define FILEPATH "C:/Users/brend/Desktop/"


////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////   MAIN   /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////



int main(void) {




	
	if (loginTest() == true) {   //test login and create first node to start setting up
		Node* headPtr = NULL;
		puts("************  Setup Mode  *************");



		bool nodeSuccess = insertNodes(&headPtr);


		//start registering racers
		bool registSuccess = false;
		if (nodeSuccess == true) {
			do {
				Racer racer = { 0 };
				registSuccess = bikeRegistration(&headPtr, &racer);
				puts("\n\n\n\n\n\n");
				while ((getchar()) != '\n');
			} while (registSuccess == true);


		}
	}
	
}  //main



bool adminSetUp(Org* orgPtr) {

	/// <summary> prompt for organization/race information and store in the org struct
	/// <params> take in pointer to organization struct to store values inside
	/// <returns> return true if it was a success, false if it was not
	
	
	bool success = false;

	bool validCost, validDist, validPercent, validJerseyCost = false;
	char validStr[80] = { '\0' };

	//Get organization name
	puts("\nEnter the organization name: ");
	fgetsRemoveNewLine(orgPtr->orgName);

	do {
		printf("Enter the cost of the race between %d and %d: ", MAX_RIDE_COST, MIN_RIDE_COST);   //Get valid Cost

		fgetsRemoveNewLine(validStr);
		validCost = validateDouble(validStr, &orgPtr->raceCost, MAX_RIDE_COST, MIN_RIDE_COST);
	} while (validCost != true);

	do {
		printf("Enter the cost of a jersey between %d and %d: ", MAX_JERSEY_COST, MIN_JERSEY_COST);   //Get valid jersey Cost
			
		fgetsRemoveNewLine(validStr);
		validJerseyCost = validateDouble(validStr, &orgPtr->jerseyCost, MAX_JERSEY_COST, MIN_JERSEY_COST);
	} while (validJerseyCost != true);

	do {
		printf("Enter the distance of the race in miles between %d and %d: ", MAX_MILES, MIN_MILES);   //Get valid Distance
			
		fgetsRemoveNewLine(validStr);
		validDist = validateDouble(validStr, &orgPtr->raceDistance, MAX_MILES, MIN_MILES);
	} while (validDist != true);

	do {
		printf("Enter the percentage of sales to be donated to charity between %d and %d: ", MAX_CHARITY, MIN_CHARITY);   //get charity %
			
		fgetsRemoveNewLine(validStr);
		validPercent = validateDouble(validStr, &orgPtr->charityPerc, MAX_CHARITY, MIN_CHARITY);
	} while (validPercent != true);
	success = true;
	

	puts("*********  Setup Complete  **********");
	return success;
	
}//adminSetup


bool loginTest(void) {

	/// <summary> test for the login passcode
	/// <params> no parameters needed
	/// <returns> return true if the passcode was entered in 3 attempts
	
	
	char attempt[80] = { 0 };
	bool success = false;
	for (int i = 0; i < LOGIN_ATTEMPTS; i++) {
		if (success == false) {
			printf("Enter the passcode. You have %d attempts remaining\n", LOGIN_ATTEMPTS - i);
			fgetsRemoveNewLine(attempt);
			if ((strcmp(attempt, PASSCODE)) == 0) {
				success = true;   ///return true if the code was correct
			}
		}
	}
	
	return success;
}//loginTest


bool bikeRegistration(Node** headPtr, Racer* racerPtr) {

	/// <summary> Register a single participant in a race. Ask which race they want to register for, their name, if they want a jersey,
	/// credit card info, and display reciept/summary. If the name entered is "quit" then quit the program
	/// <params> take in pointers to the organization and to the new racer struct to store data
	/// <returns> return true if a participant was registered, return false if "quit" was entered
	
	
	bool contin = true;
	double numberOfOrgs = displayRaceInfo(headPtr);   //display race info
	Org* orgPtr = chooseRace(headPtr,numberOfOrgs);
	racerPtr->orgOfRace = *orgPtr;



	puts("\nEnter your first name and last name to register for the race: ");
	fgetsRemoveNewLine(racerPtr->name);  //get name of racer & test for "quit"

	if ((strcmp(racerPtr->name, "Quit")) == 0) {
		if (loginTest() == true) {
			displaySummary(headPtr);
			contin = false;
		}
	}
	else if ((strcmp(racerPtr->name, "quit")) == 0) {
		if (loginTest() == true) {
			displaySummary(headPtr);
			contin = false;
		}
	}
	else if ((strcmp(racerPtr->name, "QUIT")) == 0) {
		if (loginTest() == true) {
			displaySummary(headPtr);
			contin = false;
		}
	}

	///ask participant about jersey, card, and reciept
	else {
		racerPtr->wantJersey = false;
		jerseySelection(orgPtr, racerPtr);   //prompt for jersey
		takePayment(orgPtr, racerPtr);   //take payment

		racerPtr->payment = orgPtr->raceCost;   //add
		double jerseyCost = 0;
		orgPtr->totalRiders ++;

		if (racerPtr->wantJersey == true) {   //update totals
			orgPtr->totalJerseys++;
			orgPtr->jerseySales += orgPtr->jerseyCost;
			orgPtr->totalSales += orgPtr->jerseyCost;

			racerPtr->payment += orgPtr->jerseyCost;
			jerseyCost += orgPtr->jerseyCost;
		}
		orgPtr->totalSales += orgPtr->raceCost;   //update total sales 
		orgPtr->raceSales += orgPtr->raceCost;

		puts("Do you want a receipt(y)es or (n)o ? ");   //ask for receipt
		char reciept = getValidChar(YN);
		if ((reciept == 'y') || (reciept == 'Y')) {
			printf("Race: $%-10.2lf\nJersey: $%-10.2lf\n\n", orgPtr->raceCost, jerseyCost);

			double dono = racerPtr->payment * orgPtr->charityPerc * 0.01;
			printf("\nTotal Cost: $%-10.2lf\nDonation to Charity: $%-10.2lf", racerPtr->payment, dono);   //print the amount donated

		}

		orgPtr->totalCharity += racerPtr->payment * orgPtr->charityPerc * 0.01;   //update amount donated
	}

	return contin;
}//bikeRegistration


Org* chooseRace(Node** headPtr, double numberOfOrgs) {
	/// <summary> Prompts the user which race they want to register for
	/// <params> take in the headPtr for the linked list of organizations and the number of Orgs
	/// <returns>return the organization struct that they want to register for

	puts("\n\nEnter the number of the race that you would like to register for: ");
	char inputString[80] = {'\0'};
	
	double chosenRace = 0;
	bool validDouble = false;
	while (validDouble == false) {
		fgetsRemoveNewLine(inputString);
		validDouble = validateDouble(inputString, &chosenRace, numberOfOrgs, 0);        //get the number of the race that they want
	}
	Node *currentPtr = *headPtr;

	///iterate through linked list to get to the proper node
	for (int i = 1; i < chosenRace; i++) {
		if (currentPtr != NULL) {
			currentPtr = currentPtr->nextNode;
		}
	}

	
	return &currentPtr->org;

}//choose race



double displayRaceInfo(Node** headPtr) {

	/// <summary> Display race info for a single race/organization
	/// <params> take in the pointer to the organization to pull data from
	/// <returns> return the number of organizations
	
	puts("\n**************************************************");
	puts("\nYou can register for one of the following races and a percentage will be raised for that organization");   ///display labels
	printf("\n%-10s %-40s %-15s %-10s %-15s", "Number", "Organization", "Distance", "Cost", "Percentage");

	Node* currentPtr = *headPtr;

	double i = 0;
	while (currentPtr != NULL) {
		
		//display details for every node/org as it iterates through them
		printf("\n%-10.0lf %-40s %-3.0lf miles       $%-9.2lf %%%-15.0lf", i+1,currentPtr->org.orgName, currentPtr->org.raceDistance, currentPtr->org.raceCost, currentPtr->org.charityPerc);
		i++;
		currentPtr = currentPtr->nextNode;

	}

	return i;
	

}//displayRaceInfo


void displaySummary(Node** headPtr) {

	/// <summary> Display summary for all the races/organizations
	/// <params> take in the pointer to the organization to pull data from
	/// <returns> return void	


	puts("\n\n\n************** SUMMARY **************\n\n\n");

	Node* currentPtr = *headPtr;
	char output[80] = { '\0' };
	char fileName[80] = { '\0' };
	int i = 1;

	while (currentPtr != NULL) {

		//create file pointer
		sprintf(fileName, "%soutput%d.txt", FILEPATH, i);
		FILE* filePtr;

		if ((filePtr = fopen(fileName, "w")) == NULL) {
			puts("Could not open file");
		}
		else {

			//for each detail, save it as a string and print it to the console and the file

			sprintf(output, "Organization: %s\n", currentPtr->org.orgName);
			puts(output);
			fputs(output, filePtr);

			sprintf(output, "Race Cost: $%-5.2lf\n", currentPtr->org.raceCost);
			puts(output);
			fputs(output, filePtr);

			sprintf(output, "Registrants: %-3.0lf\n", currentPtr->org.totalRiders);
			puts(output);
			fputs(output, filePtr);

			sprintf(output, "Total Race Sales: $%-5.2lf\n", currentPtr->org.raceSales);
			puts(output);
			fputs(output, filePtr);

			sprintf(output, "Jersey Cost: $%-5.2lf\n", currentPtr->org.jerseyCost);
			puts(output);
			fputs(output, filePtr);

			sprintf(output, "Jerseys Sold: %-3.0lf\n", currentPtr->org.totalJerseys);
			puts(output);
			fputs(output, filePtr);

			sprintf(output, "Total Jersey Sales: $%-5.2lf\n", currentPtr->org.jerseySales);
			puts(output);
			fputs(output, filePtr);

			sprintf(output, "Total Sales: $%-5.2lf\n", currentPtr->org.totalSales);
			puts(output);
			fputs(output, filePtr);

			sprintf(output, "Charity Percent: %-2.0lf%%\n", currentPtr->org.charityPerc);
			puts(output);
			fputs(output, filePtr);

			sprintf(output, "Charity Amount: $%-5.2lf\n\n\n\n", currentPtr->org.totalCharity);
			puts(output);
			fputs(output, filePtr);

			i++;
			currentPtr = currentPtr->nextNode;   //iterate through the nodes
			fclose(filePtr);
		}

	}

	while (*headPtr != NULL) {

		Node* currentPtr2 = *headPtr;    ///deallocate memory for each node
		if ((*headPtr != NULL)) {
			*headPtr = (*headPtr)->nextNode;
			free(currentPtr2);
			currentPtr2 = NULL;
		}
	}

}//displaySummary


void jerseySelection(Org* orgPtr, Racer* racerPtr) {

	/// <summary> Prompt the participant if they want a jersey, and if yes, ask what size. Store that data into the Racer pointer.
	/// <params> take in pointers to the org and the racer to store and update data
	/// <returns> return void
	
	
	puts("\nWould you like to purchase a jersey? Enter 'Y' for yes or 'N' for no: ");
	char decision = getValidChar(YN);
	if ((decision == 'y') || (decision == 'Y')) {
		puts("\nWhat size would you like? The options are S (small), M (medium), L (large), and X (extra-large): ");
		while ((getchar()) != '\n');
		racerPtr->jerseySize = getValidChar(SIZES);   //store jersey size
		racerPtr->wantJersey = true;
	}

}//jerseySelection


void takePayment(Org* orgPtr, Racer* racerPtr) {

	/// <summary> prompt for credit card info from a participant and validate it
	/// <params> take in pointers for the org and the racer to pull data from
	/// <returns> return void
	
	///print out their total
	double totalCost = orgPtr->raceCost;
	printf("\nCost of race: $%-10.2lf", orgPtr->raceCost);
	if (racerPtr->wantJersey == true) {
		printf("\nCost of jersey: $%-10.2lf", orgPtr->jerseyCost);   
		totalCost += orgPtr->jerseyCost;
	}
	printf("\n\nYour total is $%-10.2lf", totalCost);   

	char cardNum[80] = { 0 };

	while (getchar() != '\n');
	bool cardSuccess = false;
	do {
		puts("\n\nPlease enter you credit card number with no spaces or dashes:");     //prompt for card

		fgetsRemoveNewLine(cardNum);      //get card 
		cardSuccess = testCreditCard(cardNum);
		
	} while (cardSuccess == false);

}//takePayment


bool testCreditCard(char card[]) {

	/// <summary>validate the inputted credit card info
	/// <param>take in the string of the credit card number
	/// <returns> return true if it is a valid number, false if it is not
	
	
	bool success = true;
	if ((strlen(card)) != 13){
		puts("Error. Value entered was not the correct length, try again.");   //1st check for card: length
		success = false;
	}
	else {
		int j = 0;
		char characters[4] = { 0 };
		char digits[9] = { 0 };

		for (int i = 0; i < 13; i++) {      //2nd check for card: the proper amount of letters and numbers, should be XXXX#########
			if (i < 4) {
				characters[i] = toupper(card[i]);
			}
			else {
				digits[j] = card[i];
				j++;
			}
		}

		for (int i = 0; i < 4; i++) {
			if (success == true) {
				if ((characters[i] > 90) || (characters[i] < 65)) {    //test the first 4 chars for letters
					puts("Error. Double check your card number and try again");
					success = false;
				}
			}
		}

		for (int i = 0; i < 9; i++) {
			if (success == true) {
				if ((digits[i] > 57) || (digits[i] < 48)) {   //test the last 9 chars for numbers
					puts("Error. Double check your card number and try again");
					success = false;
				}
			}
		}
	}

	return success;
}//testCreditCard



bool validateDouble(const char* buff, double* validDblPtr, int max, int min) { 

	/// <summary> get a valid double from a string and make sure it can properly be stored and is in range
	/// <params>take in the string in which the double is going to be taken from,
	/// a pointer to where the valid double should be stored once validated,
	/// and the max and min parameters for range checking
	/// <returns>return true if the double was valid and stored properly
	

	char* end;
	errno = 0;
	bool boolean = false;
	double dblTest = strtod(buff, &end);
	if ((dblTest > max) || (dblTest < min)) {      //make sure double is in the proper range and can be stored properly in a data type of double
		printf("%s is out of range\n", buff);
	}
	else if (end == buff) {
		fprintf(stderr, "%s: not a decimal number\n", buff);
	}
	else if ('\0' != *end) {
		fprintf(stderr, "%s: extra characters at end of input: %s\n", buff, end);
	}
	else if ((DBL_MIN == dblTest || DBL_MAX == dblTest) && ERANGE == errno) {
		fprintf(stderr, "%s out of range of type long\n", buff);
	}
	else if (dblTest > INT_MAX) {
		fprintf(stderr, "%lf greater than INT_MAX\n", dblTest);
	}
	else if (dblTest < INT_MIN) {
		fprintf(stderr, "%lf less than INT_MIN\n", dblTest);
	}
	else {
		*validDblPtr = (double)dblTest;   ///store double if it passes all the checks
		boolean = true;
	}

	return boolean;
}

void fgetsRemoveNewLine(char* charptr) {

	/// <summary> get a string from fgets and remove it's newline character
	/// <params> take in the string in which the input should be stored
	/// <returns> return void
	
	
	fgets(charptr, 80, stdin);

	if (charptr[strlen(charptr) - 2] == '\n') {   //test second to last element
		charptr[strlen(charptr) - 2] = '\0';
	}
	else if (charptr[strlen(charptr) - 1] == '\n') {   //test for last element
		charptr[strlen(charptr) - 1] = '\0';
	}

}   //fgetsnewline


char getValidChar(const char* array[]) {

	/// <summary> get a char from getchar and make sure it matches with one of the values
	/// inside a given array of pointers
	/// <params> take in the array of pointers to see if the input matches one of the values
	/// <returns> return the valid char
	

	bool match = false;
	char input = 0;
	do {
		bool gaveError = false;

		input = getchar();   //read in char
		input = tolower(input);   //convert to lowercase
		int i = 0;

		while (array[i] != NULL) {   //search the  array for the char that user entered
			if (input == array[i][1]) {
				match = true;   //if there is a match, move on
			}
			i++;
		}
		if ((match == false) && (gaveError == false)) {
			puts("Error. Invalid input. Please try again");
			gaveError = true;
		}

	} while (match == false);

	return input;
}//GetValidChar



bool compareString(const char str1[80], const char str2[80]) {
	char newStr1[80] = { '\0' };
	char newStr2[80] = { '\0' };

	strcpy(newStr1, str1);
	strcpy(newStr2, str2);

	for (int i = 0; newStr1[i] != '\0'; i++) {   //conver str1 to uppercase
		if (newStr1[i] >= 'a' && newStr1[i] <= 'z') {
			newStr1[i] = newStr1[i] - 32;
		}
	}

	for (int i = 0; newStr2[i] != '\0'; i++) {   //convert str2 to uppercase
		if (newStr2[i] >= 'a' && newStr2[i] <= 'z') {
			newStr2[i] = newStr2[i] - 32;
		}
	}


	bool answer = false;
	if (strcmp(newStr1, newStr2) < 0) {
		answer = true;
	}

	return answer;

}





bool insertNodes(Node** dbheadPtr) {
	char repeat = 0;
	bool returnValue = false;
	do {

		Org org = { 0 };

		Org* orgPtr = &org;



		adminSetUp(orgPtr);

		Node* newNodePtr = malloc(sizeof(Node));    //allocate mem for new node

		free(newNodePtr);
		newNodePtr = NULL;

		if (newNodePtr != NULL) {
			newNodePtr->org = *orgPtr;   //put new org into new node

			Node* previousPtr = NULL;
			Node* currentPtr = *dbheadPtr;

			while ((currentPtr != NULL) && ((compareString(currentPtr->org.orgName, newNodePtr->org.orgName)) == true)) {    //get to correct insertion spot (alphabetical order)
				previousPtr = currentPtr;
				currentPtr = currentPtr->nextNode;
			}

			if (previousPtr == NULL) {    //if head is null, start the list
				*dbheadPtr = newNodePtr;
			}
			else {
				previousPtr->nextNode = newNodePtr;
			}

			newNodePtr->nextNode = currentPtr;
			returnValue = true;
		}
		else {
			puts("No enough memory available");    
		}
			
	
		puts("\nWould you like create another organization? Enter Y or N:");  //prompt for entering another org
		repeat = getValidChar(YN);
		while ((getchar()) != '\n');

	} while ((repeat == 'y') || (repeat == 'Y'));   //repeat until they are done

	return returnValue;

}//insertNode