//Employee.h provided by Dr. Meilin Liu, and you can modify it if you want. 

/*******************************************************
 * CS 3100-01 Data Structures and Algorithms           *
 * Tyler Cosculluela                                   *
 * Professor Liu                                       *
 * November 14, 2018                                   *
 *                                                     *
 * Project 3 - Binary Search Trees                     *
 ******************************************************/

#ifndef _Employee_
#define _Employee_

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class Employee{

public:

//Universal constructor
	Employee(int IdNum = 0, string last = "", string first = "");
//Copy constructor, initializes employee to 'person'
	Employee(const Employee &person);
//Set firstname to 'first'
	void setFirstName(string first);
//Set lastname to 'last'
	void setLastName(string last);
//Set ID to Idnum
	void setID(int IdNum);
//Return the employee's ID
	int getID() const;

//Print the employee info to the provided ostream
    void print(ostream &outs) const;

//Return the employee's firstname
	string getFirstName() const;
//Return the employee's lastname
	string getLastName() const;

//Friend >> operator, initializes 'person' with console input
	friend istream& operator>>(istream &ins, Employee &person);

//Tests equality of two employees
    bool operator==(const Employee &other) const;
//Logical comparison operators, based on employee ID
    bool operator < (const Employee &other) const;
    bool operator > (const Employee &other) const;

private:
	int ID;
	std::string lastname;
	std::string firstname;

	
};

//Nonmember << operator, calls print() with the provided ostream
ostream& operator<<(ostream &outs, const Employee &person);


#endif