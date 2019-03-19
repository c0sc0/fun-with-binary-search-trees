/*******************************************************
 * CS 3100-01 Data Structures and Algorithms           *
 * Tyler Cosculluela                                   *
 * Professor Liu                                       *
 * November 14, 2018                                   *
 *                                                     *
 * Project 3 - Binary Search Trees                     *
 ******************************************************/

#include "Employee.h"
#include <limits>


//Universal constructor
Employee::Employee(int IdNum, string first, string last) {
    ID = IdNum;
    firstname = first;
    lastname = last;

}

//Copy constructor, initializes employee to 'person'
Employee::Employee(const Employee &person) {
    ID = person.ID;
    firstname = person.firstname;
    lastname = person.lastname;

}

//Set firstname to 'first'
void Employee::setFirstName(string first) {
    firstname = first;
}

//Set lastname to 'last'
void Employee::setLastName(string last) {
    lastname = last;
}

//Set ID to Idnum
void Employee::setID(int IdNum) {
    ID = IdNum;
}

//Return the employee's ID
int Employee::getID() const{
    return ID;
}

//Return the employee's firstname
string Employee::getFirstName() const{
    return firstname;
}

//Return the employee's lastname
string Employee::getLastName() const{
    return lastname;
}

//Friend >> operator, initializes 'person' with console input
istream &operator>>(istream &ins, Employee &person) {
    int tempID;
    string tempFirst, tempLast;

    cout << "Enter the ID number" << endl;
    ins >> tempID;
    ins.ignore();
    person.setID(tempID);

    if ( ins.fail() ){                  // If the failbit is set,
        ins.clear();                    // Reset the failbit
        cout << "Invalid ID" << endl;
        ins.ignore(numeric_limits<streamsize>::max(), '\n');
        person.setID(-1);                      // Clear out the input that triggered the bit (until '\n' is reached)
        // If the input is not numeric, bad things happen
    }                                   // http://www.cplusplus.com/reference/istream/istream/ignore/

    cout << "Enter the first name" << endl;
    getline(ins, tempFirst);
    cout << "Enter the last name" << endl;
    getline(ins, tempLast);

    person.setFirstName(tempFirst);
    person.setLastName(tempLast);

    return ins;
}


//Nonmember << operator, calls print() with the provided ostream
ostream &operator<<(ostream &outs, const Employee &person) {
    person.print(outs);
    return outs;
}

//Print the employee info to the provided ostream
void Employee::print(ostream &outs) const {
    if (&outs == &cout){
        outs << "Name: " << firstname << " " << lastname << endl;
        outs << "ID: " << ID << endl;
    } else {
        outs << lastname << " " << firstname << " " << ID;
    }
}

//Tests employees for equality
bool Employee::operator==(const Employee &other) const {
    return (ID == other.getID() && firstname == other.getFirstName() && lastname == other.getLastName());
}

//Logical comparison operators, compares employees based on ID
bool Employee::operator<(const Employee &other) const {
    return (ID < other.getID());
}

//Logical comparison operators, compares employees based on ID
bool Employee::operator>(const Employee &other) const {
    return (ID > other.getID());
}
