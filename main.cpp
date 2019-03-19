/*******************************************************
 * CS 3100-01 Data Structures and Algorithms           *
 * Tyler Cosculluela                                   *
 * Professor Liu                                       *
 * November 14, 2018                                   *
 *                                                     *
 * Project 3 - Binary Search Trees                     *
 ******************************************************/

#include "BinarySearchTemplate.h"
#include <limits>

char displayMenu();
int traversalMenu();

int main() {
// Declarations

    char choice = 'c';
    string filename;
    ofstream outFile;
    ifstream inFile;
    int eID, traversal;

    cout << "\n-----------------" << endl;
    cout << "Tyler Cosculluela" << endl;
    cout << "CS3100 Project 3 - Binary Search Trees" << endl;
    cout << "14 November 2018" << endl;
    cout << "\n-----------------" << endl;

// Begin Testing

    string database = "EmployeeDB.txt";
    Employee testing;
    
    testing.setFirstName("Test");
    testing.setLastName("McTester");
    testing.setID(12345);
    
    BinarySearchTree<Employee>* empTree = new BinarySearchTree<Employee>();
    cout << "Creating employee" << endl;
    cout << "Inserting:" << endl;
    empTree->insert(testing);
    empTree->printInOrder(empTree->getRoot(), cout);
    cout << "-----------------" << endl;
    cout << "\nSearching for id 12345" << endl << endl;
    cout << *empTree->search(12345);
    cout << endl << endl;
    empTree->remove(12345);
    if (!empTree->remove(22)) cout << "Employee 22 not found" << endl;

    empTree->printInOrder(empTree->getRoot(), cout);
    empTree->reset();
    cout << "\n-----------------" << endl;
    empTree->loadFile(database,15);
    cout << "\nloading from DB" << endl << endl;
    empTree->printInOrder(empTree->getRoot(), cout);
    cout << "Size: " << empTree->BSTsize() << endl << endl;
    cout << "Deleting tree:\n" << endl;
    empTree->reset();
    cout << "Size: " << empTree->BSTsize() << endl << endl;
    delete empTree;

// Generating test input files

    ofstream outs;
    outs.open("nums.txt");
    for (int i=0; i<25; ++i){
        outs << rand() % 100 << endl;
    }
    outs.close();

    outs.open("chars.txt");
    for (int i=0; i<25; ++i){
        char c = 'a' + rand() %26;
        outs << c << endl;
    }
    outs.close();

    outs.open("strings.txt");
    for (int i=0; i<10; ++i){
        if (i % 2 != 0){
            outs << i << " More ";
        }
        outs << i << " Testing!" << endl;
    }
    outs.close();

    outs.open("dubs.txt");
    double j;
    for (int i=1; i<9; ++i){
        j = i + (0.12345 * i);
        outs << j << endl;
    }
    outs.close();

// Testing template functionality

    cout << "\n-----------------" << endl;
    cout << "Testing with ints\n" << endl;
    cout << "Inorder:" << endl;
    BinarySearchTree<int>* nums = new BinarySearchTree<int>();
    nums->loadFile("nums.txt", 25);
    nums->printInOrder(nums->getRoot(), cout);
    cout << "\n-----------------" << endl;
    cout << "Preorder:" << endl;
    nums->printPreOrder(nums->getRoot(), cout);
    cout << "\n-----------------" << endl;
    cout << "Postorder:" << endl;
    nums->printPostOrder(nums->getRoot(), cout);
    cout << endl << "Deleting tree:\n" << endl;
    delete nums;

    cout << "\n-----------------" << endl;
    cout << "Testing with doubles\n" << endl;
    BinarySearchTree<double>* dubs = new BinarySearchTree<double>();
    dubs->loadFile("dubs.txt", 10);
    dubs->printInOrder(dubs->getRoot(), cout);
    cout << endl << "Deleting tree:\n" << endl;
    delete dubs;

    cout << "\n-----------------" << endl;
    cout << "Testing with chars\n" << endl;
    BinarySearchTree<char>* chars = new BinarySearchTree<char>();
    chars->loadFile("chars.txt");
    chars->printInOrder(chars->getRoot(), cout);
    cout << endl << "Deleting tree:\n" << endl;
    delete chars;

    cout << "\n-----------------" << endl;
    cout << "Testing with strings\n" << endl;
    BinarySearchTree<string>* strings = new BinarySearchTree<string>();
    strings->loadFile("strings.txt");
    strings->printInOrder(strings->getRoot(), cout);
    cout << endl << "Deleting tree:\n" << endl;
    delete strings;
    cout << "\n-----------------" << endl;

// End Testing

    BinarySearchTree<Employee>* newTree = new BinarySearchTree<Employee>();

    if (newTree->loadFile("savedDB.txt")) {
        cout << "Loading tree from previously saved file 'savedDB.txt'" << endl;
    } else {
        cout << "'savedDB.txt' could not be found" << endl;
        cout << "Creating a new tree\n" << endl;
    }

// Begin Menu

    Employee tempEmployee;

    while (choice != 'Q'){      // Call displayMenu() every iteration until the user chooses to quit
        choice = displayMenu();
        switch (choice){                        // Switch based on the input from displayMenu()

            case 'D':
            case 'd':

                BinaryTreeNode<Employee> *rNode;
                // "Delete record"
                cout << "Please enter the ID of an employee to remove from the database" << endl;
                cin >> eID;
                cin.ignore();
                if (newTree->remove(Employee(eID))){
                    cout << "Removed employee " << eID << " from the database" << endl;
                } else {
                    cout << "Employee #" << eID << " not found" << endl;
                }

                break;

            case 'E':
            case 'e':

                BinaryTreeNode<Employee> *sNode;
                cout << "Enter employee ID ";
                cin >> eID;
                cin.ignore();
                sNode = newTree->search(Employee(eID));
                cout << "\nSearching " << newTree->BSTsize() <<" employee records" << endl;

                if (sNode != NULL){
                    cout << "Employee found:" << endl;
                    cout << *sNode << endl << endl;
                } else {
                    cout << "Employee #" << eID << " not found" << endl;
                }

                break;
            case 'I':
            case 'i':
                cout << "Enter the employee's information" << endl;
                cin >> tempEmployee;
                if (newTree->insert(tempEmployee)){
                    cout << tempEmployee << "added to the database" << endl;
                } else {
                    cout << "Error: no duplicate IDs are allowed" << endl;
                }

                break;

            case 'S':
            case 's':
                // "Save database to a file"
                traversal = traversalMenu();
                switch (traversal) {

                    case 1:
                        cout << "Saving tree to 'Inorder.txt':" << endl;
                        outFile.open("Inorder.txt");
                        newTree->printInOrder(newTree->getRoot(), outFile);
                        outFile.close();
                        break;
                    case 2:
                        cout << "Saving tree to 'Preorder.txt'" << endl;
                        outFile.open("Preorder.txt");
                        newTree->printPreOrder(newTree->getRoot(), outFile);
                        outFile.close();
                        break;
                    case 3:
                        cout << "Saving tree to 'Postorder.txt':" << endl;
                        outFile.open("Postorder.txt");
                        newTree->printPostOrder(newTree->getRoot(), outFile);
                        outFile.close();
                        break;
                    default:
                        cout << "Invalid input" << endl;
                        break;
                }
                break;
            case 'P':
            case 'p':

                // "Print the tree"
                traversal = traversalMenu();
                switch (traversal) {

                    case 1:
                        cout << "Printing tree:" << endl;
                        newTree->printInOrder(newTree->getRoot(), cout);
                        cout << "There are " << newTree->BSTsize() << " Employees in the tree" << endl;
                        break;
                    case 2:
                        cout << "Printing tree:" << endl;
                        newTree->printPreOrder(newTree->getRoot(), cout);
                        cout << "There are " << newTree->BSTsize() << " Employees in the tree" << endl;
                        break;
                    case 3:
                        cout << "Printing tree:" << endl;
                        newTree->printPostOrder(newTree->getRoot(), cout);
                        cout << "There are " << newTree->BSTsize() << " Employees in the tree" << endl;
                        break;
                    default:
                        cout << "Invalid input" << endl;
                        break;
                }


                break;
            case 'Q':
            case 'q':
                // "Quit"
                choice = 'Q';
                break;
            default:
                cout << "Invalid input" << endl;
                break;
        }
    }
    cout << "Saving database to 'savedDB.txt'" << endl;
    outFile.open("savedDB.txt");
    newTree->printInOrder(newTree->getRoot(), outFile);
    outFile.close();
    delete newTree;
    cout << "\nTree deleted" << endl;
    cout << "Goodbye!" << endl;



    return 0;
}

// Prints menu choices and receives input for the switch case
char displayMenu() {
    char input = 'O';

    cout << "(I)nsert record" << endl;
    cout << "(D)elete record" << endl;
    cout << "(E)mployee ID search" << endl;
    cout << "(S)ave database to a file" << endl;
    cout << "(P)rint the database" << endl;
    cout << "(Q)uit" << endl;

    cout << "\nWhat would you like to do? ";
    cin >> input;
    cin.ignore();

    if ( cin.fail() ){                  // If the failbit is set,
        cin.clear();                    // Reset the failbit

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        input = 'O';                      // Clear out the input that triggered the bit (until '\n' is reached)
        // If the input is a char, the while loop will run indefinitely
    }                                   // http://www.cplusplus.com/reference/istream/istream/ignore/

    cout << endl;
    return input;                       // Return the choice
}

// Prints menu choices and receives input for the switch case
int traversalMenu(){
    int input = 0;
    cout << "Please select the traversal algorithm " << endl;
    cout << "1. Inorder" << endl;
    cout << "2. Preorder" << endl;
    cout << "3. Postorder\n" << endl;
    cin >> input;
    cin.ignore();

    if ( cin.fail() ){                  // If the failbit is set,
        cin.clear();                    // Reset the failbit

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        input = 1;                      // Clear out the input that triggered the bit (until '\n' is reached)
        // If the input is not numeric, the while loop will run indefinitely
    }                                   // http://www.cplusplus.com/reference/istream/istream/ignore/

    cout << endl;
    return input;
}