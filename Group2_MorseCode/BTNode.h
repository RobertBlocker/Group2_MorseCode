#ifndef BTNODE_H
#define BTNODE_H

#include <iostream>
#include <sstream>
#include <string>

using std::ostream;
using std::ostringstream;
using std::string;

/** A binary tree node */
template<class T>
struct BTNode {
    // Data fields
    T data;  // Stores some data in the node.
    BTNode<T>* left, * right;  // Stores pointers to the left and right child.

    // Constructor
    BTNode(const T&, BTNode<T>* = NULL, BTNode<T>* = NULL);

    // Destructor
    virtual ~BTNode();  // Avoid warning messages.

    // Class-member function
    void tree_builder(string, const BTNode<T>*);
    void tree_builder(string, int, const BTNode<T>*);
    virtual string to_string() const;  // Returns a string containing the data stored in the node.
};

// Constructor
template<class T>
BTNode<T>::BTNode(const T& data, BTNode<T>* left, BTNode<T>* right) : data(data), left(left), right(right) {}

// Destructor
template<class T>
BTNode<T>::~BTNode() {}

//Wrapper function
template<class T>
void BTNode<T>::tree_builder(string line, const BTNode<T>* root) {
    tree_builder(line, 0, root);
}//end wrapper

//Function to build tree of morse code 
template<class T>
void BTNode<T>::tree_builder(string line, int pos, const BTNode<T>* root) {
    pos++;
    bool finished = false;

    if (pos == line.size()) {
        finished = true;

        if (root == NULL) {
            BTNode<T>* new_node = new BTNode<T>(line.at(0));
            root = new_node;
        }
        else {
            root->data = line.at(0);
        }
    }

    if (finished == false) {
        if(line.at(pos) == '.') {
            if (root == NULL) {
                BTNode<T>* new_node = new BTNode<T>('0');
                root = new_node;
                root->left = tree_builder(line, pos, root->left);
            }
            else {
                root->left = tree_builder(line, pos, root->left);
            }
        }//end if

        if (line.at(pos) == '-') {
            if (root == NULL) {
                BTNode<T>* new_node = new BTNode<T>('0');
                root = new_node;
                root->right = tree_builder(line, pos, root->right);
            }
            else {
                root->right = tree_builder(line, pos, root->right);
            }
        }//end if
    }
}//end tree_builder

/** Returns a string containing the data stored in the node.
    @return: a string containing the data stored in the node
*/
template<class T>
string BTNode<T>::to_string() const {
    ostringstream oss;
    oss << data;
    return oss.str();
}

// Stream insertion operator
template<class T>
ostream& operator << (ostream& out, const BTNode<T>* node) { return out << node->to_string(); }

#endif
