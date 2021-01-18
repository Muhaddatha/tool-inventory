#include<iostream>
#include<string>
#include <fstream>
#include "LinkedList-1.h"
#include "Record.h"
#include "UnsortedLinkedList.h"
/*
Author: Muhaddatha Abdulghani
Date created: 4/10/19
Date updated: 4/12/19
File: SourceLab11.cpp
Purpose: The purpose of theis file is to execute all operation on the list
of items in inventory.
*/
bool debugging = true;
int main() {
	Record blankRecord = { 0, '.', 0 , 0.0 };
	std::fstream recordFile;
	std::ofstream logFile;
	//check if files exist and are open
	recordFile.open("recordFile.txt");
	logFile.open("logFile.txt");
	if (!recordFile || !recordFile.is_open()) {
		std::cout << "Error opening recordFile." << std::endl;
		system("pause");
		return 0;
	}
	if (!logFile.is_open() || !logFile) {
		std::cout << "Error opening logFile." << std::endl;
		system("pause");
		return 0;
	}
	recordFile.seekg(recordFile.tellg(), std::ios::beg);
	for (int i = 0; i < 100; i++) {
		recordFile.write(reinterpret_cast<const
			char*>(&blankRecord), sizeof(Record));
	}
	recordFile.close();
	//used to save record
	//int unsortedArrayIndex = 0;
	int recorDNum, Quantity, toolNameLength = 20;
	float toolCost;
	//filing unsorted and sorted arrays with default values
	Record sortedArray[100];
	Record unsortedArray[100];
	LinkedList sortedList;
	unsortedLinkedList unsortedList;
	for (int i = 0; i < 100; i++) {
		unsortedArray[i] = blankRecord;
		sortedArray[i] = blankRecord;
	}
	//for (int i = 0; i < 100; i++) {
	// std::cout << unsortedArray[i].recordNum << " "<< unsortedArray[i].quantity << " " << unsortedArray[i].cost << std::endl;
	// std::cout << sortedArray[i].recordNum << " " <<sortedArray[i].quantity << " " << sortedArray[i].cost << std::endl;
	//}
	int option;
	std::cout <<
		"******************************************************" << std::endl;
	std::cout << " Welcome to this program" << std::endl;
		std::cout <<"******************************************************" << std::endl;
	do {
		std::cout << "1. Add a record." << std::endl;
		std::cout << "2. Update a record." << std::endl;
		std::cout << "3. Delete a record." << std::endl;
		std::cout << "4. List a record." << std::endl;
		std::cout << "5. List all records." << std::endl;
		std::cout << "6. Exit and save to file." << std::endl;
		std::cout << "Option: "; std::cin >> option;
		while (std::cin.fail()) {
			std::cout << "Please enter a vlid integer (1-5): ";
				std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> option;
		}
		switch (option) {
		case 1: {
			//check if record already exists or not
			bool recordExists = false;
			Record recordToAdd;
			std::cout << "Please enter the record number: "; std::cin >> recorDNum;
				while (std::cin.fail() || (recorDNum <=
					0 || recorDNum > 100)) {
					std::cin.clear();
					std::cin.ignore(256, '\n');
					std::cout << "Please enter a valid record number : ";
						std::cin >> recorDNum;
				}
			for (int i = 0; i < 100; i++) {
				if (sortedArray[i].recordNum
					== recorDNum) {
					recordExists =
						true;
					break;
				}
			}
			if (recordExists == false) {
				recordToAdd.recordNum = recorDNum;
				std::string tool;
				std::cout << "Please enter the tool's name: ";
					std::cin.ignore(1000, '\n');
				std::getline(std::cin, tool);
				if (tool.length() < 20) {
					toolNameLength =
						tool.length();
				}
				for (int i = 0; i < tool.length(); i++)
				{
					recordToAdd.toolName[i] =
						tool.at(i);
				}
				for (int i = toolNameLength; i < 20;
					i++) {
					recordToAdd.toolName[i] =
						'\0';
				}
				std::cout << "Please enter " << tool <<
					"'s quantity: "; std::cin >> Quantity;
				while (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(256, '\n');
					std::cout << "Please enter a valid quantity integer : ";
						std::cin >> Quantity;
				}
				recordToAdd.quantity = Quantity;
				std::cout << "Please enter the tool's price: "; 
				std::cin.ignore(1000, '\n'); std::cin >> toolCost;
					while (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(256, '\n');
						std::cout << "Please enter a valid number for price: ";
							std::cin >> toolCost;
					}
				recordToAdd.cost = toolCost;
				//1. add to unsorted array.
				int unsortedArrayAddComparisons = 0;
				for (int i = 0; i < 100; i++) {
					if
						(unsortedArray[i].recordNum == 0) {
						unsortedArray[i]
							= recordToAdd;
						break;
					}
					unsortedArrayAddComparisons++;
				}
				//unsortedArrayIndex++;
				//std::cout << "Information stored in unsorted array." << std::endl;
					//2. Add to sorted array.
					sortedArray[recorDNum - 1] =
					recordToAdd;
				//std::cout << "Information stored in sorted array." << std::endl;
					int sortedLinkedListComparisons = 0;
				int unsortedLinkedListComparisons = 0;
				//3. Add to unsorted linked list
				unsortedList.insertRecord(recordToAdd,
					unsortedLinkedListComparisons);
				//4. Add to sorted linked list
				sortedList.insertRecord(recordToAdd,
					sortedLinkedListComparisons);
				//5. Write to file
				recordFile.open("recordFile.txt");
				recordFile.seekg(recordFile.tellg(),
					std::ios::beg);
				recordFile.seekp(recorDNum *
					sizeof(Record), std::ios::beg);
				recordFile.write(reinterpret_cast<const
					char*>(&recordToAdd), sizeof(Record));
				recordFile.close();
				logFile <<
					"*****************************************************************" <<
					std::endl;
				logFile << "Operation: adding record ("
					<< recorDNum << ", " << tool << ", " << Quantity << ", " << toolCost <<
					")" << std::endl;
				logFile << "Unsorted array comparisons: " << unsortedArrayAddComparisons << std::endl;
					logFile << "Unsorted linked list comparisons: " << unsortedLinkedListComparisons << std::endl;
					logFile << "Sorted linked list comparisons : " << sortedLinkedListComparisons << std::endl;
					logFile << std::endl;
			}
			else {
				std::cout << "Error while creating account.This record number already exists." << std::endl;
			}
			break;
		}
		case 2: {
			Record recordToUpdate;
			bool recordExists = false;
			//check if record exists or not.
			std::cout << "What record number would you like to update : "; std::cin >> recorDNum;
				while (std::cin.fail() || (recorDNum <= 0 ||
					recorDNum > 100)) {
					std::cout << "Please enter a valid record number : ";
						std::cin.ignore(256, '\n');
					std::cin.clear();
					std::cin >> recorDNum;
				}
			for (int i = 0; i < 100; i++) {
				if (sortedArray[i].recordNum ==
					recorDNum) {
					recordExists = true;
					break;
				}
			}
			if (recordExists == false) {
				std::cout << "Sorry his account doesn't exist." << std::endl;
			}
			else {
				recordToUpdate.recordNum = recorDNum;
				std::string tool;
				std::cout << "What is the updated tool's name: "; std::cin.ignore(1000, '\n'); std::getline(std::cin, tool);
					if (tool.length() < 20) {
						toolNameLength =
							tool.length();
					}
				for (int i = 0; i < toolNameLength;
					i++) {
					recordToUpdate.toolName[i] =
						tool.at(i);
				}
				recordToUpdate.toolName[toolNameLength]
					= '/0';
				std::cout << "What is the updated quantity: "; std::cin >> Quantity;
					while (std::cin.fail()) {
						std::cout << "Please enter a valid quantity integer : ";
							std::cin.ignore(256, '\n');
						std::cin.clear();
						std::cin >> Quantity;
					}
				recordToUpdate.quantity = Quantity;
				std::cout << "What is the updated price: "; std::cin >> toolCost;
					while (std::cin.fail()) {
						std::cout << "Please enter a valid number for price: ";
							std::cin.ignore(256, '\n');
						std::cin.clear();
						std::cin >> toolCost;
					}
				recordToUpdate.cost = toolCost;
				//1. update unsorted array
				int unsortedArrayUpdateComparisons = 0;
				for (int i = 0; i < 100; i++) {
					if
						(unsortedArray[i].recordNum != 0) {
						if
							(unsortedArray[i].recordNum == recorDNum) {
							unsortedArray[i] = recordToUpdate;
							break;
						}
						unsortedArrayUpdateComparisons++;
					}
				}
				//2. update sorted array
				sortedArray[recorDNum - 1] =
					recordToUpdate;
				//3. update unsorted linked list
				int sortedListUpdateComparisons = 0;
				int unsortedListUpdateComparisons = 0;
				unsortedList.updateRecord(recordToUpdate,
					unsortedListUpdateComparisons);
				//4. update sorted linked list
				sortedList.updateRecord(recordToUpdate,
					sortedListUpdateComparisons);
				//5. update file
				recordFile.open("recordFile.txt");
				recordFile.seekg(recordFile.tellg(),
					std::ios::beg);
				recordFile.seekp(recorDNum *
					sizeof(Record), std::ios::beg);
				recordFile.write(reinterpret_cast<const
					char*>(&recordToUpdate), sizeof(Record));
				recordFile.close();
				logFile <<
					"*****************************************************************" <<
					std::endl;
				logFile << "Operation: updating record (" << recorDNum << ", " << tool << ", " << Quantity << ", " << toolCost <<
						")" << std::endl;
				logFile << "Unsorted array comparisons:" << unsortedArrayUpdateComparisons << std::endl;
				logFile << "Unsorted linked list comparisons: " << unsortedListUpdateComparisons << std::endl;
				logFile << "Sorted linked list comparisons : " << unsortedArrayUpdateComparisons << std::endl;
				logFile << std::endl;
			}
		}
				break;
		case 3: {
			int recordToDelete;
			std::cout << "What record number would you like to delete: "; std::cin >> recordToDelete;
				while (std::cin.fail() || recordToDelete <= 0
					|| recordToDelete > 100) {
					std::cin.clear();
					std::cin.ignore(256, '\n');
					std::cout << "Please enter a valid record number between 1 - 100: "; std::cin >> recordToDelete;
				}
			bool recordExists = false;
			for (int i = 0; i < 100; i++) {
				if (sortedArray[i].recordNum ==
					recordToDelete) {
					recordExists = true;
					break;
				}
			}
			if (recordExists == true) {
				sortedArray[recordToDelete - 1] =
					blankRecord;
				//unsortedArrayIndex--;
				int unsortedDeleteComparisons = 0;
				for (int i = 0; i < 100; i++) {
					if
						(unsortedArray[i].recordNum != 0) {
						if
							(unsortedArray[i].recordNum == recordToDelete) {
							unsortedArray[i] = blankRecord;
							break;
						}
						unsortedDeleteComparisons++;
					}
				}
				int sortedLinkedlistDeleteComparisons =
					0;
				sortedList.deleteRecord(recordToDelete,
					sortedLinkedlistDeleteComparisons);
				int unsortedLinkedListDeleteComparisons
					= 0;
				unsortedList.deleteRecord(recordToDelete,
					unsortedLinkedListDeleteComparisons);
				Record temp;
				recordFile.open("recordFile.txt");
				recordFile.seekg(recordFile.tellg(),
					std::ios::beg);
				recordFile.seekp(recordToDelete *
					sizeof(Record), std::ios::beg);
				recordFile.write(reinterpret_cast<char*>(&temp), sizeof(Record));
				recordFile.close();
				std::string toolName;
				//for (int i = 0; i < 20; i++) {
				//if (temp.toolName[i] !='\0') {
					// toolName.at(i) =temp.toolName[i];
					// if (temp.toolName[i]== '\0') {
					// break;
					//}
					//}
					//}
					recordFile.open("recordFile.txt");
					recordFile.seekg(recordFile.tellg(),
						std::ios::beg);
					recordFile.seekp(recordToDelete *
						sizeof(Record), std::ios::beg);
					recordFile.write(reinterpret_cast<const
						char*>(&blankRecord), sizeof(Record));
					recordFile.close();
					logFile <<
						"*****************************************************************" <<
						std::endl;
					logFile << "Operation: deleting record (" << recordToDelete << ", " << toolName << ", " << temp.quantity << ", "
							<< temp.cost << ")" << std::endl;
					logFile << "Unsorted array comparisons:" << unsortedDeleteComparisons << std::endl;
					logFile << "Unsorted linked list comparisons: " << unsortedLinkedListDeleteComparisons << std::endl;
					logFile << "Sorted linked list comparisons : " << sortedLinkedlistDeleteComparisons << std::endl;
					logFile << std::endl;
}
			else {
				std::cout << "Sorry, this record number does not exist." << std::endl;
			}
				}
				break;
		case 4: {
			int recordNumberToPrint;
			std::cout << "What record number would you like to see : "; std::cin >> recordNumberToPrint;
				while (std::cin.fail() ||
					recordNumberToPrint > 100 || recordNumberToPrint <= 0) {
					std::cin.clear();
					std::cin.ignore(256, '\n');
					std::cout << "Please enter a valid number in this range(0 - 100) : "; std::cin >> recordNumberToPrint;
				}
			bool recordExists = false;
			for (int i = 0; i < 100; i++) {
				if (sortedArray[i].recordNum ==
					recordNumberToPrint) {
					recordExists = true;
					break;
				}
			}
			if (recordExists == true) {
				std::cout << "Printing from sorted array..." << std::endl;
				std::cout << "record number: " << sortedArray[recordNumberToPrint - 1].recordNum << "/ ";
				std::cout << "Tool name: ";
				for (int i = 0; i < 20; i++) {
					if
						(sortedArray[recordNumberToPrint - 1].toolName[i] != '\0') {
						std::cout <<
							sortedArray[recordNumberToPrint - 1].toolName[i];
					}
				}
				std::cout << "/ ";
				std::cout << "Tool quantity: " <<
					sortedArray[recordNumberToPrint - 1].quantity << "/ ";
				std::cout << "Tool price: " <<
					sortedArray[recordNumberToPrint - 1].cost << std::endl << std::endl;
				int unsortedArrayPrintComparisons = 0;
				std::cout << "Printing from unsorted array..." << std::endl;
					for (int i = 0; i < 100; i++) {
						if
							(unsortedArray[i].recordNum != 0) {
							if
								(unsortedArray[i].recordNum == recordNumberToPrint) {
								std::cout
									<< "record number: " << unsortedArray[i].recordNum << std::endl;
								std::cout <<
									"Tool name: ";
								for (int j
									= 0; j < 20; j++) {
									if (unsortedArray[i].toolName[j] != '\0') {
										std::cout << unsortedArray[i].toolName[j];
									}
								}
								std::cout
									<< "Tool quantity: " << unsortedArray[i].quantity << "/ ";
								std::cout
									<< "Tool cost: " << unsortedArray[i].cost << std::endl << std::endl;
								break;
							}
							unsortedArrayPrintComparisons++;
						}
					}
				int sortedListPrintComparisons = 0,
					unsortedListPrintComparisons = 0;
				std::cout << "Printing from sorted linked list..." << std::endl;
					sortedList.printRecord(recordNumberToPrint, sortedListPrintComparisons);
				std::cout << "Printing from unsorted linked list.." << std::endl;
				unsortedList.printRecord(recordNumberToPrint, unsortedListPrintComparisons);
				Record blankrecord1 = { 0, ' ', 0,
				0.0 };
				std::cout << "Printing from file..." <<
					std::endl;
				recordFile.open("recordFile.txt");
				recordFile.seekg(recordFile.tellg(),
					std::ios::beg);
				recordFile.seekp(recordNumberToPrint *
					sizeof(Record), std::ios::beg);
				recordFile.read(reinterpret_cast<char*>(&blankrecord1),
					sizeof(Record));
				recordFile.close();
				std::string toolNAME = "tool";
				std::cout << "Record number: " <<
					blankrecord1.recordNum << "/ ";
				std::cout << "Tool name: ";
				for (int i = 0; i < 20; i++) {
					if
						(blankrecord1.toolName[i] != '\0') {
						std::cout <<
							blankrecord1.toolName[i];
						//toolNAME.at(i)= blankrecord1.toolName[i];
					}
				}
				//for (int k = 0; k < 20; k++) {
				//toolNAME.at(k) =blankrecord1.toolName[k];
				//}
				std::cout << "/ ";
				std::cout << "Tool quantity: " <<
					blankrecord1.quantity << "/ ";
				std::cout << "Tool cost: " <<
					blankrecord1.cost << std::endl << std::endl;
				logFile <<
					"*****************************************************************" <<
					std::endl;
				logFile << "Operation: printing record (" << recordNumberToPrint << ", " << toolNAME << ", " <<
						blankrecord1.quantity << ", " << blankrecord1.cost << ")" << std::endl;
				logFile << "Unsorted array comparisons:" << unsortedArrayPrintComparisons << std::endl;
					logFile << "Unsorted linked list comparisons: " << unsortedListPrintComparisons << std::endl;
					logFile << "Sorted linked list comparisons : " << sortedListPrintComparisons << std::endl;
					logFile << std::endl;
			}
			else {
				std::cout << "Sorry, this record does not exist." << std::endl;
			}
		}
				break;
		case 5: {
			std::cout << "Printing sorted array.." <<
				std::endl;
			for (int i = 0; i < 100; i++) {
				if (sortedArray[i].recordNum != 0) {
					std::cout << "Record number: " << sortedArray[i].recordNum << " / ";
						std::cout << "Tool name: ";
					for (int j = 0; j < 20; j++)
					{
						if
							(sortedArray[i].toolName[j] != '\0') {
							std::cout
								<< sortedArray[i].toolName[j];
						}
					}
					std::cout << "/ ";
					std::cout << "Tool quantity: " << sortedArray[i].quantity << " / ";
						std::cout << "Tool cost: "
						<< sortedArray[i].cost << std::endl << std::endl;
				}
			}
			std::cout << "Printing unsorted array..." <<
				std::endl;
			for (int i = 0; i < 100; i++) {
				if (unsortedArray[i].recordNum != 0) {
					std::cout << "Record number: " << unsortedArray[i].recordNum << " / ";
					std::cout << "Tool name: ";
					for (int j = 0; j < 20; j++)
					{
						if
							(unsortedArray[i].toolName[j] != '\0') {
							std::cout
								<< unsortedArray[i].toolName[j];
						}
					}
					std::cout << "/ ";
					std::cout << "Tool quantity: " << unsortedArray[i].quantity << " / ";
					std::cout << "Tool cost: " << unsortedArray[i].cost << std::endl << std::endl;
				}
			}
			std::cout << "Printing from sorted linked list..." << std::endl;
			sortedList.printAllrecords();
			std::cout << "Printing from unsorted linked list..." << std::endl;
			unsortedList.printAllRecords();
			std::cout << "Printing all records from file..." << std::endl;
			recordFile.open("recordFile.txt");
			recordFile.seekg(recordFile.tellg(),
				std::ios::beg);
			for (int i = 0; i < 100; i++) {
				Record blank = { 0, ' ', 0, 0.0 };
				//recordFile.seekg(recordFile.tellg(),std::ios::beg);
				recordFile.seekp(i * sizeof(Record), std::ios::beg);
				recordFile.read(reinterpret_cast<char*>(&blank), sizeof(Record));
				if (blank.recordNum != 0) {
					std::cout << "Record number: " << blank.recordNum << " / ";
						std::cout << "Tool name: ";
					for (int i = 0; i < 20; i++)
					{
						if
							(blank.toolName[i] != '\0') {
							std::cout
								<< blank.toolName[i];
						}
					}
					std::cout << "/ ";
					std::cout << "Tool quantity:" << blank.quantity << " / ";
						std::cout << "Tool cost: " << blank.cost << std::endl << std::endl;
				}
			}
			//std::cout << std::endl;
		}
				break;
		case 6: {
			break;
		}
		default: {
			std::cout << "Please enter a valid option from the menu : " << std::endl;
				break;
		}
			}
			std::cout << std::endl << std::endl;
		}while (option != 6);
		logFile.close();
		sortedList.~LinkedList();
		unsortedList.~unsortedLinkedList();
		system("pause");
		return 0;
		}