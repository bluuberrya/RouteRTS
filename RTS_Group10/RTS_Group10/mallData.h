#pragma once

#ifndef MALLDATA_H
#define MALLDATA_H
#include "main.h"

struct mall
{
	// Data
	string mallID;
	string name;
	string address;
	string coordinate;

	// Pointer
	mall* nextAddress;
};


// mall list
class mallList
{
	mall* head = NULL; // start with a empty list

public:
	mallList() {};

	mall* getHead()
	{
		return head;
	}

	mall* createNewNode(string mallID, string name, string address, string coordinate)
	{
		// 1. Create structure in the heap location
		mall* newnode = new mall;

		// 2. Assigning the data into the node
		newnode->mallID = mallID;
		newnode->name = name;
		newnode->address = address;
		newnode->coordinate = coordinate;

		newnode->nextAddress = NULL; // initially set to NULL

		// 3. Return back the new created node to the other function
		return newnode;
	}

	// Insert into sorted carlist
	mall* insertIntoSortedMallList(string mallID, string name, string address, string coordinate)
	{
		// Call the create function to create a newnode
		mall* newnode = createNewNode(mallID, name, address, coordinate);

		// Situation 1: Empty carlist
		if (head == NULL)
		{
			head = newnode;
		}

		// Situation 2: Smaller or Equal to the mallID - Insert into the front of original mallList
		else if (mallID <= head->mallID)
		{
			newnode->nextAddress = head;
			head = newnode;
		}

		// Situation 3: More than the malID head value - Insert into the end of original mallLIst
		else
		{
			mall* current = head->nextAddress;
			mall* prev = head;

			while (current != NULL)
			{
				if (mallID <= current->mallID)
				{
					break;
				}

				prev = current;
				current = current->nextAddress;
			}

			prev->nextAddress = newnode;
			newnode->nextAddress = current;
		}

		return head;
	}

	mall* insertToEndOfList(string mallID, string name, string address, string coordinate)
	{
		// Call the create function to create a new node
		mall* newnode = createNewNode(mallID, name, address, coordinate);

		// Add to the list
		if (head == NULL)
		{
			head = newnode;
		}
		else // list not empty?
		{
			mall* current = head;

			while (current->nextAddress != NULL)
			{
				current = current->nextAddress;
			}

			current->nextAddress = newnode;
		}

		return head;
	}


	void displayLinkedListItem() // Big O Notation is O(n)
	{
		mall* current = head;

		int lineNumber = 1; // initialize line number to 1
		while (current != NULL)
		{
			if (lineNumber >= 1) // only print data from line 2 onwards
			{
				cout << left << setw(80) << current->mallID;
				cout << setw(10) << current->name;
				cout << setw(18) << current->address;
				cout << setw(10) << current->coordinate;
				cout << endl;
			}
			current = current->nextAddress;
			lineNumber++; // increment line number for each iteration
		}
	}

	void readMallListFromCSV() {
		string mallID;
		string name;
		string address;
		string coordinate;

		ifstream file("mallList.csv"); // open csv file

		while (file.good())
		{
			getline(file, mallID, ',');

			if (mallID == "")
			{
				break;
			}

			getline(file, mallID, ',');
			getline(file, name, ',');
			getline(file, address, ',');
			getline(file, coordinate, ',');

			insertToEndOfList(mallID, name, address, coordinate);
		}

		file.close();
	}

	//Find mall by mall ID
	string findMallById(string mallID) {
		mall* current = head;
		while (current != NULL) {
			if (current->mallID == mallID) {
				return current->name, "|", current->address, "|", current->coordinate;
			}
			current = current->nextAddress;
		}
		return "";
	}

	//// Filtering Criteria 1 - Price
	//carlist searchBasedOnCarPrice(carlist head, string price)
	//{
	//	car* current = head.getHead();
	//	carlist filteredList;
	//	int i = 0;

	//	while (current != NULL)
	//	{
	//		if (price == current->carPrice)
	//		{
	//			i++;

	//			filteredList.insertToEndOfList(current->carID, current->carTitle, current->carPrice, current->carRegDate, current->carMileage,
	//				current->carFuelType, current->carTransmission, current->carEngineSize, current->carDoors, current->carColour,
	//				current->carBodyType, current->carURL, current->carSaleDate);
	//		}

	//		current = current->nextAddress;
	//	}

	//	if (i == 0)
	//	{
	//		cout << "No cars matching the search criteria found." << endl;
	//	}
	//	else
	//	{
	//		cout << endl;
	//		filteredList.displayLinkedListItem();
	//		cout << endl << "*******End of carlist*******" << endl;
	//	}

	//	return filteredList;
	//}

};


#endif