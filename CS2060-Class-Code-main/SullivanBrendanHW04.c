#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#define STUDENTS 3
#define GRADE_CATEGORIES 4
#define CATEGORIES "1. Class Activity 2. Homework 3. Quizzes 4. Final "
const double GRADE_CATEGORY_WEIGHT[] = { 0.1, 0.4, 0.3, 0.2 };


void getStudentGrades(double gradeArray[STUDENTS][GRADE_CATEGORIES]);
void calculateGrade(double gradeArray[STUDENTS][GRADE_CATEGORIES], double finalGradeArray[STUDENTS]);
void displayFinalGrades(double finalGradeArray[STUDENTS]);
void displayAllGrades(double gradeArray[STUDENTS][GRADE_CATEGORIES]);


int main(void) {
	double gradeArray[STUDENTS][GRADE_CATEGORIES] = {0};
	double finalGradeArray[STUDENTS] = {0};

	printf("This program will calculate the grades for these categories: %s\n", CATEGORIES);   //display initial header
	puts("The category weights are:\n");
	for (int i = 0; i < GRADE_CATEGORIES; i++) {
		printf("Category %d weight is %.2lf\n", i + 1, GRADE_CATEGORY_WEIGHT[i]);
	}
	puts("\n\nEnter the Grades:");

	getStudentGrades(gradeArray);   //prompt for grades
	displayAllGrades(gradeArray);   //display the 2D array
	calculateGrade(gradeArray, finalGradeArray);   //calculate the final grades
	puts("\n\n*******   FINAL GRADES  *******\n");   //display the final grades
	displayFinalGrades(finalGradeArray);

	return 0;
}   //Main



void getStudentGrades(double gradeArray[STUDENTS][GRADE_CATEGORIES]) {
	int newGrade = 0;
	int scannedVar = 0;
	bool validInput = false;

	for (int i = 0; i < STUDENTS; i++) {   //Get grades for 1 student
		puts("\n");
		for (int j = 0; j < GRADE_CATEGORIES; j++) {   //Get grade for each category for that 1 student
			do {
				printf("Enter the grade for Student %d, Category %d: ", i+1, j+1);
				scannedVar = scanf("%d", &newGrade);   //Get new Grade
				while (getchar() != '\n');
				if (scannedVar == 1) {
					if (newGrade <= 105 && newGrade >= 0) {
						gradeArray[i][j] = newGrade;
						validInput = true;
					}

					else {
						puts("Invalid Input. Please try again.");   //if invalid
					}
				}

				else {
					puts("Invalid Input. Please try again.");   //if scannedVar = false
				}

			} while (validInput == false);   //repeat until a valid input is recieved
		}


	}
}   //get1StudentGrades


void calculateGrade(double gradeArray[STUDENTS][GRADE_CATEGORIES], double finalGradeArray[STUDENTS]) {
	double weightedCatGrade = 0;
	double weightedTotalGrade = 0;
	for (int i = 0; i < STUDENTS; i++) {   //for each student
		weightedTotalGrade = 0;
		for (int j = 0; j < GRADE_CATEGORIES; j++) {
			weightedCatGrade = gradeArray[i][j] * GRADE_CATEGORY_WEIGHT[j];   //calculate the weighted grade
			weightedTotalGrade += weightedCatGrade;
		}
		finalGradeArray[i] = weightedTotalGrade;   //store weighted grade into 1-D array
	}
}   //calculateGrade


void displayFinalGrades(double finalGradeArray[STUDENTS]) {
	char gradeLetter = 0;
	double totalOfGrades = 0;
	for (int i = 0; i < STUDENTS; i++) {
		if (finalGradeArray[i] >= 90) {   //Find the letter grade
			gradeLetter = 'A';
		}
		else if (finalGradeArray[i] >= 80) {
			gradeLetter = 'B';
		}
		else if (finalGradeArray[i] >= 70) {
			gradeLetter = 'C';
		}
		else if (finalGradeArray[i] >= 60) {
			gradeLetter = 'D';
		}
		else {
			gradeLetter = 'F';
		}

		printf("\nStudent %d:  %.1lf  %c", i+1, finalGradeArray[i], gradeLetter);
		totalOfGrades += finalGradeArray[i];
	}

	printf("\nClass average: %.1lf\n\n", totalOfGrades / STUDENTS);
}   //displayFinalGrades


void displayAllGrades(double gradeArray[STUDENTS][GRADE_CATEGORIES]) {

	for (int i = 0; i < STUDENTS; i++) {   //iterate through each student
		printf("\nStudent %d: ", i+1);
		for (int j = 0; j < GRADE_CATEGORIES; j++) {   //iterate through each category
			printf("%5.0lf", gradeArray[i][j]);
		}
	}
}   //displayAllGrades

