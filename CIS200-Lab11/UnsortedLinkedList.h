#pragma once
#include<iostream>
#include "Record.h"
/*
Author: Muhaddatha Abdulghani
Date created: 4/10/19
Date updated: 4/12/19
File: UnsortedLinkedList.h
Purpose: The is the implementation file for the unsorted linked list
*/
struct Node {
	Record record;
	Node* next = nullptr;
};
class unsortedLinkedList {
private:
	Node* head;
	int length;
public:
	/*
	Author: Muhaddatha Abdulghani
	precondition: none
	postcondition: an object is created
	Description: This a class constructor
	*/
	unsortedLinkedList() {
		head = nullptr;
		length = 0;
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: none
	postcondition: none
	Description: This method inserts a record at the beginning of the
	list
	*/
	void insertRecord(Record recordToInsert, int& comparisons) {
		Node* temp = new Node;
		temp->record = recordToInsert;
		if (head == nullptr) {
			head = temp;
		}
		else {
			temp->next = head;
			head = temp;
		}
		temp = nullptr;
		length++;
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: record exists in the list
	postcondition: none
	Description: record is updated in the file
	*/
	void updateRecord(Record updatedRecord, int& numberOfComparisons) {
		if (head == nullptr) {
			std::cout << "Error - The sorted linked list is empty.Cannot update record." << std::endl;
				return;
		}
		Node* updaterecordptr = head;
		while (updaterecordptr != nullptr &&
			updaterecordptr->record.recordNum != updatedRecord.recordNum) {
			numberOfComparisons++;
			updaterecordptr = updaterecordptr->next;
		}
		if (updaterecordptr->record.recordNum ==
			updatedRecord.recordNum) {
			for (int i = 0; i < 20; i++) {
				updaterecordptr->record.toolName[i] =
					updatedRecord.toolName[i];
			}
			updaterecordptr->record.quantity =
				updatedRecord.quantity;
			updaterecordptr->record.cost =
				updatedRecord.cost;
			std::cout << "Record updated in unsorted linked list successfully." << std::endl;
				std::cout << std::endl;
		}
		else {
			std::cout << "Error-record not updated in unsorted linked list." << std::endl << std::endl;
		}
		updaterecordptr = nullptr;
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: record exists in the list
	postcondition: none
	Description: record is removed from the list
	*/
	void deleteRecord(int& recordNumber, int& comparisons) {
		if (head == nullptr)
			return;
		bool foundRecord = false;
		Node* recordFinder = head;
		if (head->record.recordNum == recordNumber) {
			foundRecord = true;
			if (head->next != nullptr) {
				head = head->next;
			}
			else {
				head = nullptr;
			}
			comparisons = 1;
			delete recordFinder;
			length--;
			recordFinder = nullptr;
			std::cout << "Record deleteed from unsorted linked list." << std::endl;
				return;
		}
		Node* trail = recordFinder;
		while (recordFinder != nullptr &&
			recordFinder->record.recordNum != recordNumber) {
			comparisons++;
			trail = recordFinder;
			recordFinder = recordFinder->next;
		}
		if (recordFinder->record.recordNum == recordNumber) {
			std::cout << "record number " <<
				recordFinder->record.recordNum << "deleted from unsorted linked list." <<
				std::endl;
			foundRecord = true;
			trail->next = recordFinder->next;
			recordFinder->next = nullptr;
			delete recordFinder;
			recordFinder = nullptr;
			length--;
		}
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: record exists in the list
	postcondition: none
	Description: record is printed to the screen
	*/
	void printRecord(int& recordNumber, int& comparisons) {
		Node* recordFinder = head;
		if (head == nullptr)
			return;
		while (recordFinder != nullptr &&
			recordFinder->record.recordNum != recordNumber) {
			comparisons++;
			recordFinder = recordFinder->next;
		}
		if (recordFinder->record.recordNum == recordNumber) {
			std::cout << "Record number: " <<
				recordFinder->record.recordNum << "/ ";
			std::cout << "Tool name: ";
			for (int i = 0; i < 20; i++) {
				if (recordFinder->record.toolName[i] !=
					'\0') {
					std::cout <<
						recordFinder->record.toolName[i];
				}
			}
			std::cout << "/ ";
			std::cout << "Tool quantity: " <<
				recordFinder->record.quantity << "/ ";
			std::cout << "Tool cost: " <<
				recordFinder->record.cost << std::endl;
			std::cout << std::endl;
		}
		else {
			std::cout << "Error-value not found in unsorted linked list." << std::endl;
		}
		recordFinder = nullptr;
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: the list is not empty
	postcondition: none
	Description: This method prints all the records to the screen
	*/
	void printAllRecords() {
		if (head == nullptr) {
			std::cout << "Error-There are no records in the insorted linked list." << std::endl;
				return;
		}
		Node* printPtr = head;
		for (int i = 0; i < 100; i++) {
			if (printPtr != nullptr &&
				printPtr->record.recordNum > 0) {
				std::cout << "Record number: " <<
					printPtr->record.recordNum << "/ ";
				std::cout << "Tool name: ";
				for (int i = 0; i < 20; i++) {
					if
						(printPtr->record.toolName[i] != '/0') {
						std::cout <<
							printPtr->record.toolName[i];
					}
				}
				std::cout << "/ ";
				std::cout << "Tool quantity: " <<
					printPtr->record.quantity << "/ ";
				std::cout << "Tool price: " <<
					printPtr->record.cost << std::endl << std::endl;
			}
			printPtr = printPtr->next;
			if (printPtr == nullptr) {
				break;
			}
		}
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: none
	postcondition: object is destructed
	Description: This is a class destructor.
	*/
	~unsortedLinkedList() {
		Node* deletePtr = head;
		while (deletePtr != nullptr) {
			head = head->next;
			delete deletePtr;
			length--;
			deletePtr = head;
		}
		deletePtr = nullptr;
	}
};
