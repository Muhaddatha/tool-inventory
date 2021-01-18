#pragma once
#include<iostream>
#include "Record.h"
/*
Author: Muhaddatha Abdulghani
Date created: 4/10/19
Date updated: 4/12/19
File: LinkedList.h
Purpose: This is the implementation file for the sorted linked list.
*/
struct node {
	Record record;
	node* next = nullptr;
};
class LinkedList {
private:
	node* head;
	int length;
public:
	/*
	Author: Muhaddatha Abdulghani
	precondition: none
	postcondition: an object of this class is created
	Description: This is a constructor for this class.
	*/
	LinkedList() {
		head = nullptr;
		length = 0;
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: none
	postcondition: a new record is inserted into the linked list
	Description: This method adds a recored to the sorted linked list
	*/
	void insertRecord(Record recordToinsert, int& comparisons) {
		/*if (recordExists(recordToinsert.recordNum)) {
		std::cout << "Error-This record number
		already exists in the sorted linked list." << std::endl;
		return;
		}*/
		node* temp = new node;
		temp->record = recordToinsert;
		if (head == nullptr || head->record.recordNum >
			recordToinsert.recordNum) {
			//insert at beginning
			comparisons = 1;
			temp->next = head;
			head = temp;
			temp = nullptr;
			length++;
			return;
		}
		node* curPtr = head;
		node* prevPtr = curPtr;
		while (curPtr != nullptr && curPtr->record.recordNum <
			recordToinsert.recordNum) {
			comparisons++;
			prevPtr = curPtr;
			curPtr = curPtr->next;
		}
		//insert at end
		if (curPtr == nullptr) {
			prevPtr->next = temp;
		}
		else {
			//insert at middle
			temp->next = curPtr;
			prevPtr->next = temp;
		}
		temp = nullptr;
		length++;
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: record exists in the list
	postcondition:Record is removed from the list
	Description: This method removes a record from the list
	*/
	void deleteRecord(int& recordNumber, int& comparisons) {
		try {
			if (isEmpty()) {
				throw std::string();
			}
		}
		catch (std::string) {
			std::cout << "Error while deleting(sorted linked list) - Record doesn't exist or list is empty." << std::endl;
				return;
		}
		bool foundRecord = false;
		node* recordFinder = head;
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
		node* trail = recordFinder;
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
	precondition:record exists in list
	postcondition: record is updated
	Description: record is updated
	*/
	void updateRecord(Record updatedRecord, int& numberOfComparisons) {
		if (head == nullptr) {
			std::cout << "Error - The sorted linked list is empty.Cannot update record." << std::endl;
				return;
		}
		node* updaterecordptr = head;
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
			std::cout << "Record updated in soted linked list successfully." << std::endl;
				std::cout << std::endl;
		}
		else {
			std::cout << "Error-record not updated in sorted linked list." << std::endl << std::endl;
		}
		updaterecordptr = nullptr;
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: record exists in the list
	postcondition: print to screen
	Description: one record is printed to the screen
	*/
	void printRecord(int &recordNumber, int& comparisons) {
		try {
			if (isEmpty())
				throw std::string();
		}
		catch (std::string) {
			std::cout << "Error while printing(sorted linked list) - Record odesn't exist or list is empty." << std::endl;
				return;
		}
		node* recordFinder = head;
		if (head == nullptr)
			return;
		while (recordFinder != nullptr &&
			recordFinder->record.recordNum != recordNumber) {
			comparisons++;
			recordFinder = recordFinder->next;
		}
		if (recordFinder->record.recordNum == recordNumber) {
			std::cout << "Record number: " <<
				recordFinder->record.recordNum << " /";
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
			std::cout << "Error-value not found in sorted linked list." << std::endl;
		}
		recordFinder = nullptr;
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: the list is not empty
	postcondition: all recors are printed to the screen
	Description: This method prints all records to the screen
	*/
	void printAllrecords() {
		try {
			if (isEmpty()) {
				throw std::string();
			}
		}
		catch (std::string) {
			std::cout << "Error while priting(sorted linked list) - List is empty." << std::endl;
				return;
		}
		//print all non-zero
		node* printPtr = head;
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
				std::cout << "Tool quatiy: " <<
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
	postcondition: none
	Description: object is destructed
	*/
	~LinkedList() {
		node* deletePtr = head;
		while (deletePtr != nullptr) {
			head = head->next;
			delete deletePtr;
			length--;
			deletePtr = head;
		}
		deletePtr = nullptr;
	}
private:
	/*
	Author: Muhaddatha Abdulghani
	precondition: none
	postcondition: return of a boolean
	Description: This method checks to see if the list is empty
	*/
	bool isEmpty() {
		if (length == 0) {
			return true;
		}
		return false;
	}
};