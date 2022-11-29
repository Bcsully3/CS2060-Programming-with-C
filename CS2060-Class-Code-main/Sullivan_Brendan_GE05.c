#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


typedef struct pet {
	char name[30];
	int age;
}Pet;

typedef struct Node {
	struct pet thisPet;
	struct Node* nextPtr;
}Node;

void insertPet(Node** headPtr);
bool compareString(const char str1[30], const char str2[30]);
void displayPets(Node* headPtr);
void writeToFile(Node* headPtr);
void removePet(Node* headPtr);
void removeAllPets(Node* headPtr);

int main(void) {
	Node *mainHeadPtr = NULL;
	insertPet(&mainHeadPtr);
	return 0;
}//main


void insertPet(Node** headPtr) {
	char repeat = 0;
	do {
		Node* nodePtr = malloc(sizeof(Node));
		if (nodePtr != NULL) {
			char temp[3] = { 0 };
			while ((getchar()) != '\n');
			puts("\nPlease enter the name of your pet: ");
			fgets(nodePtr->thisPet.name, 30, stdin);
			while ((getchar()) != '\n');
			puts("\nPlease enter the pet's age: ");
			fgets(temp, 3, stdin);
			nodePtr->thisPet.age = atoi(temp);
		}

		if (headPtr == NULL) {    //Start List
			headPtr = nodePtr;
			headPtr->nextPtr = NULL;
		}
		else {   //if there are already nodes
			bool inserted = false;
			if (compareString(headPtr->thisPet.name, nodePtr->thisPet.name) == false) {							//if the node goes at the beginning
				nodePtr->nextPtr = headPtr;
				headPtr = nodePtr;
			}
			else {
				Node* currentNodePtr = headPtr;
				do {
					if (compareString(currentNodePtr->nextPtr->thisPet.name, nodePtr->thisPet.name) == false){	//if node goes in the middle
						nodePtr->nextPtr = currentNodePtr->nextPtr;
						currentNodePtr->nextPtr = nodePtr;
						inserted = true;
					}
					else {
						currentNodePtr = currentNodePtr->nextPtr;
					}
				} while ((currentNodePtr->nextPtr != NULL) && (inserted==false));

				if (inserted == false) {																		//if node goes at the end
					currentNodePtr->nextPtr = currentNodePtr;
				}
			}
			
		}
		puts("\nWould you like to enter another pet? Enter Y or N:");
		while ((getchar()) != '\n');
		repeat = getchar();
	} while ((repeat == 'y') || (repeat == 'Y'));
	
}//insertPet



bool compareString(const char str1[30],const char str2[30]) {
	char newChar = 0;
	int beforetoUpper = 0;
	char newStr1[30] = { 0 };
	char newStr2[30] = { 0 };

	for (int i = 0; i < strlen(str1); i++) {   //convert both strings to upper
		beforetoUpper = atoi(&str1[i]);       //atoi does whole str to a large int; will need to TYPECAST
		newChar = toupper(beforetoUpper);		// make 2 temp arrays and use string copy ; return value of strcomp to save space////////////////////////
		newStr1[i] = newChar;
	}
	for (int i = 0; i < strlen(str1); i++) {
		newStr2[i] = toupper(atoi(&str2[i]));
	}

	bool answer;
	int temp = strcmp(newStr1, newStr2);
	if (temp >= 0) {   //str1 is greater
		answer = false;
	}
	else {   //str1 is less
		answer = true;
	}

	return answer;

}

void displayPets(Node* headPtr) {

}

void writeToFile(Node* headPtr) {

}

void removePet(Node* headPtr) {

}

void removeAllPets(Node* headPtr) {

}