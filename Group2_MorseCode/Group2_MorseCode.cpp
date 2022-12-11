// Group2_MorseCode.cpp

#include "BTNode.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

void menu();
void mainMenu();

char choice;
static int COUNT = 10;

int main() {

	menu();

	return 0;
	system("pause");
}

//Prints menu to select encoding or decoding
template<class T>
void menu() {
	string msg, encoded_str, decoded_str;
	BTNode<T>* head = new BTNode<T>(' ');
	ifstream rfile("Morse_Code.txt");
	string line;
	
	do {
		if(!rfile) {
			cout << "Error: File not found" << endl;
			system("pause");
			return;
		}

		while(getline(rfile, line)) {
			tree_builder(line, head);
		}
		rfile.close();
		//*******
		tree_printer(head);

		mainMenu();

		switch (choice) {

		case 'e':
			cout << "Enter message to encode: " << endl;
			cin >> msg;
			for (int i = 0; i < msg.size(); i++) {
				if (msg.at(i) == ' ') {
					encoded_str.append(" ");
				}
				else {
					encoded_str += encode(msg.at(i), "", head);
					std::replace(encoded_str.begin(), encoded_str.end(), "1", "");
				}
				cout << "Message Encoded into Morse Code: " << encoded_str << endl;
			}//end for loop
			

		case 'd':
			cout << "Enter message to decode: " << endl;
			cin >> msg;
			for (int i = 0; i < msg.size(); i++) {
				decoded_str += decode(msg, 0, head);
			}
			cout << "Morse Code Message Decoded: " << decoded_str << endl;

		case 'q':
			break;
		}//end of switch

	} while (choice != 'q');
}//end of menu

//Menu Display for console
void mainMenu() {

	cout << "Main Menu" << endl;
	cout << "e - Encode Message" << endl;
	cout << "d - Decode Message" << endl;
	cout << "q - Quit" << endl;
	cout << "Choose Option: ";
	cin >> choice;
	cout << endl;

}

// Converts lower-case plain-text (with no spaces) to Morse Code form.
template<class T>
static string encode(char letter, string encoded_str, const BTNode<T>* root) {
	if (root->val == letter) {
		return encoded_str += " 1";
	}
	else {
		string left_str, right_str;
		if (root->left != NULL) {
			left_str = (root->left->val != ' ') ? encode(letter, encoded_str + ".", root->left) : NULL;
			if (left_str.find("1") != string::npos) {
				return right_str;
			}
		}
		return "";
	}
}//end encode

//Decode function taking positions of chars (.) and (-)
template<class T>
static char decode(string to_decode, int pos, const BTNode<T>* root) {
	if (to_decode.at(pos) == '.') {
		pos += 1;
		return decode(to_decode, pos, root->left);
	}
	else if (to_decode.at(pos) == '-') {
		pos += 1;
		return decode(to_decode, pos, root->right);
	}
	return root->val;
}//end decode


//Wrapper function
template<class T>
BTNode<T>* tree_builder(string line, const BTNode<T>* head) {
	tree_builder(line, 0, head);
}//end wrapper

//Function to build tree of morse code 
template<class T>
BTNode<T>* tree_builder(string line, int pos, const BTNode<T>* root) {
	pos++;
	bool finished = false;

	if (pos == line.size()) {
		finished = true;

		if (root == NULL) {
			BTNode<T>* new_node = new BTNode<T>(line.at(0));
			root = new_node;
		}
		else {
			root->val = line.at(0);
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
	return root;
}//end tree_builder

//Function to print morse code tree to console
template<class T>
static void tree_print(const BTNode<T>* root, int space) {
	if (root == NULL) { return; }

	space += COUNT;

	tree_print(root->right, space);

	cout << endl;
	for (int i = COUNT; i < space; i++) { cout << " "; }
	cout << root->val << endl;

	tree_print(root->left, space);
}

//Wrapper function
template<class T>
static void tree_printer(const BTNode<T>* root) {
	tree_print(root, 0);
}//end wrapper
