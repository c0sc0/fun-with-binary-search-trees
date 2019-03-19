//Employee.h provided by Dr. Meilin Liu, and you can modify it if you want.

/*******************************************************
 * CS 3100-01 Data Structures and Algorithms           *
 * Tyler Cosculluela                                   *
 * Professor Liu                                       *
 * November 14, 2018                                   *
 *                                                     *
 * Project 3 - Binary Search Trees                     *
 ******************************************************/

#ifndef _BinaryTreeNode_
#define _BinaryTreeNode_
#include <iostream>
#include <cstdlib>
#include "Employee.h"

using namespace std;

template <class Thing>
class BinaryTreeNode{
public:
	Thing item;
	BinaryTreeNode * parent;
	BinaryTreeNode * left;
	BinaryTreeNode * right;
/*
	BinaryTreeNode(){
	    item = Thing();
	    parent = NULL;
	    right = NULL;
	    left = NULL;
	}
*/
	BinaryTreeNode(Thing _item, BinaryTreeNode * parentptr = NULL, BinaryTreeNode * rightptr = NULL, BinaryTreeNode *leftptr = NULL) {
        item = _item;
        parent = parentptr;
        right = rightptr;
        left = leftptr;
    }

    ~BinaryTreeNode(){
	    cout << "Deleting " << *this << endl;
	}
	/*
	friend istream& operator >> (istream &ins, BinaryTreeNode &node){

	}*/

    friend ostream& operator<<(ostream &outs, const BinaryTreeNode &node){
        outs << node.item;
        return outs;
    }
};

#endif
