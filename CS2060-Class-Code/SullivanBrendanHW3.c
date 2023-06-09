#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_HOURS 10
#define HOURS_FOR_MIN_CHARGE 2
#define END_OF_DAY -1
#define	MAX_COST 75
#define HOURLY_COST 10
#define MIN_COST 35


double getValidInput(void); // function prototypes
int calculateCharge(int hours);
void displayCharge(int tempCost, int tempHours);
void displaySummary(int totalHours, int totalEarnings, int numberOfBoards);




int main(void) { //MAIN
	int totalHours = 0;
	int totalEarnings = 0;
	int numberOfBoards = 0;
	int tempHours = 0;
	double doubleTempHours = 0;
	int tempCost = 0;
	bool dayEnded = false;
	
	do {

		doubleTempHours = getValidInput(); //get input
		tempHours = (int)doubleTempHours;

		if (tempHours == -1) { //check for -1
			displaySummary(totalHours, totalEarnings, numberOfBoards);   //display day summary
			dayEnded = true;
		}

		else {

			if ((double)tempHours < doubleTempHours) {   //check if the input was a decimal
				tempHours++;
			}

			tempCost = calculateCharge(tempHours);   //calculate charge
			displayCharge(tempCost, tempHours);   //display transaction summary
			totalHours += tempHours;   //add up hours and cost
			totalEarnings += tempCost;
			numberOfBoards++;
		}
	} while (dayEnded == false);   //loop until day is over

	return 0;
}//main



double getValidInput(void) {
	double hours = 0;
	bool validInput = false;
	int scanner = 0;

	do {
		puts("\nPlease enter the number of hours that the board is being rented for");
		scanner = scanf("%lf", &hours);  //take input
		while (getchar() != '\n');   //clear buffer
		if (scanner == 1) {   //make sure scanf returned true
			
			if (hours > MAX_HOURS) {   //if the hours exceed the max
				printf("Error, the number of hours cannot exceed %d", MAX_HOURS);
			}
			else if (hours <= 0 && hours > END_OF_DAY) {   //If the hours are between -1 and 0
				puts("Error, the number of hours must be greater than 0");
			}
			else if (hours < END_OF_DAY) {   //if the hours are less than the end of day
				puts("Error, the number of hours must be greater than 0");
			}
			else {   //if valid, end loop
				validInput = true;
			}

		}
		else {   //if scanf returns false
			printf("Error, value must be a number between 0 and %d", MAX_HOURS);
		}
	} while (validInput == false);

	return hours;   // if its valid, return hours

}//getValidInput



int calculateCharge(int hours) {
	int tempCost = 0;
	if (hours <= HOURS_FOR_MIN_CHARGE) {   //if the hours are less than the minimum rental
		tempCost = MIN_COST;
	}
	else if (hours <= MAX_HOURS) {   // if the an hourly cost needs to be calculated
		tempCost = MIN_COST + (HOURLY_COST * (hours - HOURS_FOR_MIN_CHARGE));

		if (tempCost > MAX_COST) {   //if the cost is over the max, make it the max
			tempCost = MAX_COST;
		}
	}

	return tempCost;

}//calculateCharge



void displayCharge(int tempCost, int tempHours) {   //display details of single transaction
	printf("\n\n%-20s%-20s%-10s", "Number of Boards:", "Number of hours:", "Cost:");
	printf("\n%-20d%-20d%-10d", 1, tempHours, tempCost);
	puts("\n\n\n");
}

void displaySummary(int totalHours, int totalEarnings, int totalNumberOfBoards) {
	
	puts("\n\n********** End of day **********");

	if (totalNumberOfBoards == 0) {   //if no boards were rented
		puts("No boards were rented");
	}

	else {   //display totals
		printf("%-30s%-30s%-15s", "Total Number of Boards:", "Total Number of hours:", "Money made:");
		printf("\n%-30d%-30d%-15d", totalNumberOfBoards, totalHours, totalEarnings);
		puts("\n\n\n");
	}
	
}//displaySummary


