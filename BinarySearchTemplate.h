//Employee.h provided by Dr. Meilin Liu, and you can modify it if //you want.

/*******************************************************
 * CS 3100-01 Data Structures and Algorithms           *
 * Tyler Cosculluela                                   *
 * Professor Liu                                       *
 * November 14, 2018                                   *
 *                                                     *
 * Project 3 - Binary Search Trees                     *
 ******************************************************/

#ifndef _BinarySearchTemplate_
#define _BinarySearchTemplate_

#include <cstdlib>
#include <fstream>
#include <sstream>
#include "BinaryTreeNode.h"
#include "Employee.h"

using namespace std;

template <class Thing>
class BinarySearchTree {

private:
    BinaryTreeNode<Thing> *root;
    int size;

public:

    BinarySearchTree();
    ~BinarySearchTree();
// Called by reset(), recursively deletes nodes in the tree
    void clear(BinaryTreeNode<Thing> *node);
// Called by the destructor (or explicitly), calls clear() to delete the tree
    void reset();

// Inserts an item T into its proper spot in the tree
    bool insert(Thing T);
// Removes an item T from the tree
    bool remove(Thing T);

// Returns a pointer to the node holding the target item, or a null pointer if the target is not found
    BinaryTreeNode<Thing>* search(Thing T) const;
// Finds the lowest item in a subtree, used in the remove() function
    BinaryTreeNode<Thing>* findLowest(BinaryTreeNode<Thing>* subTree) const;

// Returns true if tree is empty
    bool isEmpty();
// Returns the size of the tree
    int BSTsize();
// Returns a pointer to the root node
    BinaryTreeNode<Thing>* getRoot();

// Prints the tree to the provided ostream using an Inorder traversal
    void printInOrder(BinaryTreeNode<Thing>* node, ostream& outs);
// Prints the tree to the provided ostream using a Preorder traversal
    void printPreOrder(BinaryTreeNode<Thing>* node, ostream& outs);
// Prints the tree to the provided ostream using a Postorder traversal
    void printPostOrder(BinaryTreeNode<Thing>* node, ostream& outs);

// Loads the tree from an input file
    bool loadFile(const string &filename, int count = 100);

};

template <class Thing>
    BinarySearchTree<Thing>::BinarySearchTree() {
        root = NULL;
        size = 0;
    }

template <class Thing>
    BinarySearchTree<Thing>::~BinarySearchTree() {
        reset();
    }

// Called by reset(), recursively deletes nodes in the tree
template <class Thing>
    void BinarySearchTree<Thing>::clear(BinaryTreeNode<Thing> *node) {
// Recursively call clear() until the left and right subtrees are traversed
        if (node->left != NULL) clear(node->left);
        if (node->right != NULL) clear(node->right);
        delete node;
    }

// Called by the destructor (or explicitly), calls clear() to delete the tree
template <class Thing>
    void BinarySearchTree<Thing>::reset() {
        if (root == NULL) return;   // Make sure we're not deleting something that has already been deleted
        size = 0;
        clear(root);                // clear() will recursively delete the tree nodes
        root = NULL;
    }

// Inserts an item T into its proper spot in the tree
template <>
bool BinarySearchTree<string>::insert(string T) {
// insert(), specialized for strings

    if (this->search(T) != NULL) return false; //no duplicates

    if (T.empty()){
        cout << "Invalid ID" << endl;
        return false;
    }

    if (isEmpty()){
        root = new BinaryTreeNode<string>(T);
        size = 1;
        return true;
    }

    BinaryTreeNode<string>* temp = root;
    BinaryTreeNode<string>* tempParent = NULL;  //Backing up a level so we can correctly insert T as a
                                                //left child or right child

    while (temp != NULL){

        if (T < temp->item){
            tempParent = temp;
            temp = temp->left;
        } else {
            tempParent = temp;
            temp = temp->right;
        }
    }

    BinaryTreeNode<string>* insertionNode = new BinaryTreeNode<string>(T);
    insertionNode->parent = tempParent;

    if (T < tempParent->item) tempParent->left = insertionNode;
    else tempParent->right = insertionNode;
    ++size;
    return true;
}

// Inserts an item T into its proper spot in the tree
template <class Thing>
bool BinarySearchTree<Thing>::insert(Thing T) {

    if (this->search(T) != NULL) return false; //no duplicates

    if (T < 0){
        cout << "Invalid ID" << endl;
        return false;
    }

    if (isEmpty()){
        root = new BinaryTreeNode<Thing>(T);
        size = 1;
        return true;
    }

    BinaryTreeNode<Thing>* temp = root;
    BinaryTreeNode<Thing>* tempParent = NULL;   //Backing up a level so we can correctly insert T as a
                                                //left child or right child

    while (temp != NULL){

        if (T < temp->item){
            tempParent = temp;
            temp = temp->left;
        } else {
            tempParent = temp;
            temp = temp->right;
        }
    }

    BinaryTreeNode<Thing>* insertionNode = new BinaryTreeNode<Thing>(T);
    insertionNode->parent = tempParent;

    if (T < tempParent->item) tempParent->left = insertionNode;
    else tempParent->right = insertionNode;
    ++size;
    return true;
}

// Returns a pointer to the node holding the target item, or a null pointer if the target is not found
template <class Thing>
    BinaryTreeNode<Thing>* BinarySearchTree<Thing>::search(Thing T) const{
        BinaryTreeNode<Thing>* temp = root;

        while (temp != NULL){
            if (T < temp->item){
                temp = temp->left;
            } else if (T > temp->item){
                temp = temp->right;
            }
            else return temp;
        }
        return NULL;    //T not found
    }

// Finds the lowest item in a subtree, used in the remove() function
template <class Thing>
    BinaryTreeNode<Thing>* BinarySearchTree<Thing>::findLowest(BinaryTreeNode<Thing>* subTree) const {
        if (subTree == NULL) subTree = root;
        BinaryTreeNode<Thing>* temp = subTree;
        while (temp != NULL && temp->left != NULL){
            temp = temp->left;
        }
        return temp;
    }

// Removes an item T from the tree
template <class Thing>
    bool BinarySearchTree<Thing>::remove(Thing T) {

        // This one is a doozy

        // I realized too far into writing this function that I should have made it recursive

        // For each branch (no child/left/right/both), we check the parent of the item to be removed
        // to determine whether the item is a left child or a right child

        BinaryTreeNode<Thing>* temp = this->search(T);

        if (temp == NULL){
            return false;
        }

        BinaryTreeNode<Thing>* tempParent = temp->parent;

        if (temp->left == NULL && temp->right == NULL){ // no children
            if (tempParent != NULL){
                if (tempParent->left == temp){
                    delete temp;
                    tempParent->left = NULL;
                    size--;
                    return true;
                } else {
                    delete temp;
                    tempParent->right = NULL;
                    size--;
                    return true;
                }
            } else {            //deleting tree of size 1 (only the root)
                delete temp;
                root = NULL;
                size--;
                return true;
            }
        }  // no children

        if (temp->left != NULL && temp->right == NULL){ // left child
            if (tempParent != NULL){
                if (tempParent->left == temp){
                    BinaryTreeNode<Thing>* tempChild = temp->left;
                    delete temp;
                    tempChild->parent = tempParent;
                    tempParent->left = tempChild;
                    size--;
                    return true;
                } else {
                    BinaryTreeNode<Thing>* tempChild = temp->left;
                    delete temp;
                    tempChild->parent = tempParent;
                    tempParent->right = tempChild;
                    size--;
                    return true;
                }
            } else {
                BinaryTreeNode<Thing>* tempChild = temp->left;
                delete temp;
                root = tempChild;
                size--;
                return true;
            }
        }  // left child

        if (temp->left == NULL && temp->right != NULL){ // right child
            if (tempParent != NULL){
                if (tempParent->left == temp){
                    BinaryTreeNode<Thing>* tempChild = temp->right;
                    delete temp;
                    tempChild->parent = tempParent;
                    tempParent->left = tempChild;
                    size--;
                    return true;
                } else {
                    BinaryTreeNode<Thing>* tempChild = temp->right;
                    delete temp;
                    tempChild->parent = tempParent;
                    tempParent->right = tempChild;
                    size--;
                    return true;
                }
            } else {
                BinaryTreeNode<Thing>* tempChild = temp->right;
                delete temp;
                root = tempChild;
                size--;
                return true;
            }


        }  // right child

        // If we have made it this far, there are two children

        BinaryTreeNode<Thing>* newRoot = findLowest(temp->right);
        BinaryTreeNode<Thing>* rootParent = newRoot->parent;
        if (rootParent->left == newRoot){
            rootParent->left = newRoot->right;
        } else {    //if the node being deleted has a child, it will be on the right
            rootParent->right = newRoot->right;
        }

        temp->item = newRoot->item;
        delete newRoot;
        size--;
        return true;
    }

// Returns the size of the tree
template <class Thing>
    int BinarySearchTree<Thing>::BSTsize(){
        return size;
    }

// Returns true if tree is empty
template <class Thing>
    bool BinarySearchTree<Thing>::isEmpty(){
        return root == NULL;
    }

// Prints the tree to the provided ostream using an Inorder traversal
template <class Thing>
    void BinarySearchTree<Thing>::printInOrder(BinaryTreeNode<Thing>* node, ostream& outs) {
        if (node == NULL) return;   //base case

        printInOrder(node->left, outs);
        outs << *node << endl;
        printInOrder(node->right, outs);

    }

// Prints the tree to the provided ostream using a Preorder traversal
template <class Thing>
void BinarySearchTree<Thing>::printPreOrder(BinaryTreeNode<Thing>* node, ostream& outs) {
    if (node == NULL) return;   //base case

    outs << *node << endl;
    printPreOrder(node->left, outs);
    printPreOrder(node->right, outs);

}

// Prints the tree to the provided ostream using a Postorder traversal
template <class Thing>
void BinarySearchTree<Thing>::printPostOrder(BinaryTreeNode<Thing>* node, ostream& outs) {
    if (node == NULL) return;   //base case

    printPostOrder(node->left, outs);
    printPostOrder(node->right, outs);
    outs << *node << endl;

}

// Returns a pointer to the root node
template <class Thing>
    BinaryTreeNode<Thing>* BinarySearchTree<Thing>::getRoot(){
        return root;
    }

// Loads the tree from an input file
template <>
    bool BinarySearchTree<Employee>::loadFile(const string &filename, int count) {
// Template specialized for Employees

        ifstream ins(filename.c_str());
        if (!ins){
            cout << "Error: unable to open file" << endl;
            return false;
        }
        string tempLast, tempFirst, numStr;
        int tempNum;

        getline(ins, tempLast, ' ');    //get first line until first space
        getline(ins, tempFirst, ' ');   //get from first space to second space
        getline(ins, numStr);           //get from second space to newline
        istringstream(numStr) >> tempNum;   //cast numStr to an int with an istringstream <sstream>
        Employee temp(tempNum, tempFirst, tempLast);

        root = new BinaryTreeNode<Employee>(temp);
        size = 1;

        while (getline(ins, tempLast, ' ') && size < count){     //get first line until first space
            getline(ins, tempFirst, ' ');                       //get from first space to second space
            getline(ins, numStr);                               //get from second space to newline
            istringstream(numStr) >> tempNum;                   //cast numStr to an int with an istringstream <sstream>

            temp.setID(tempNum);                                //fill the variables of temp
            temp.setFirstName(tempFirst);
            temp.setLastName(tempLast);

            this->insert(temp);                                   //insert into the tree
        }
        ins.close();
        return true;
    }

// Loads the tree from an input file
template <class Thing>
    bool BinarySearchTree<Thing>::loadFile(const string &filename, int count) {
        Thing T;

        //Template for everything else (ints, chars, doubles)

        ifstream ins(filename.c_str());
        if (!ins){
            cout << "Error: unable to open file" << endl;
            return false;
        }
        ins >> T;

        root = new BinaryTreeNode<Thing>(T);// new stack with first line as top
        size = 1;

        while (ins >> T && size < count){
            this->insert(T);
        }
        ins.close();
    }

// Loads the tree from an input file
template <>
    bool BinarySearchTree<string>::loadFile(const string &filename, int count) {

        //Template specialized for strings

        ifstream ins(filename.c_str());
        if (!ins){
            cout << "Error: unable to open file" << endl;
            return false;
        }
        string temp;
        getline(ins, temp);

        root = new BinaryTreeNode<string>(temp);// new stack with first line as top
        size = 1;

        while (getline(ins, temp) && size < count){
            this->insert(temp);
        }
        ins.close();
    }



#endif

