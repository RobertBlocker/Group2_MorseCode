// Group2_MorseCode.cpp

#include "BTNode.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

void menu();
void main_menu();

char choice;
static int COUNT = 10;

int main() {

	cout << "MORSE CODE BINARY TREE";
	menu();

	return 0;
}//end main

//Menu Display for console
void main_menu() {

	cout << endl;
	cout << "Main Menu" << endl;
	cout << "e - Encode Message" << endl;
	cout << "d - Decode Message" << endl;
	cout << "q - Quit" << endl;
	cout << "Choose Option: ";
	cin >> choice;
	cout << endl;
}//end mainMenu function

/** Converts lower-case and non-spaced plain-text to Morse Code form.
	@param letter: singular letter from inputted string
	@param encoded_str: encoded string
	@param root: root of binary tree
	@return: encoded string of morse code
*/
string encode(char letter, string encoded_str, const BTNode<char>* root) {
	if (root->data == letter) {
		return encoded_str += " 1";
	}
	string left_str, right_str;
	if (root->left) {
		left_str = (root->left->data != ' ') ? encode(letter, encoded_str + ".", root->left) : NULL;
		if (left_str.find("1") != string::npos) {
			return left_str;
		}
	}

	if (root->right) {
		right_str = (root->right->data != ' ') ? encode(letter, encoded_str + "-", root->right) : NULL;
		if (right_str.find("1") != string::npos) {
			return right_str;
		}
	}
	return "";
}//end encode

/** Takes positions of chars (.) and (-) to decode Morse Code into English text
	@param to_decode: string of morse code
	@param pos: position in string
	@param root: root of binary tree
	@return: decoded string in text
*/
char decode(string to_decode, int pos, const BTNode<char>* root) {
	if (pos == to_decode.size()) {
		return root->data;
	}

	if (to_decode.at(pos) == '.') {
		pos += 1;
		return decode(to_decode, pos, root->left);
	}
	if (to_decode.at(pos) == '-') {
		pos += 1;
		return decode(to_decode, pos, root->right);
	}
	return ' ';
}//end decode

/** Builds a visualizer of the binary tree of morse code.
	@param root: root of binary tree
	@param space: spacing for tree nodees
*/
void tree_print(const BTNode<char>* root, int space) {
	if (!root) { return; }

	space += COUNT;

	tree_print(root->right, space);

	cout << endl;
	for (int i = COUNT; i < space; i++) { cout << " "; }
	cout << root->data << endl;

	tree_print(root->left, space);
}

//Wrapper function
void tree_printer(const BTNode<char>* root) {
	tree_print(root, 0);
}//end wrapper

//Prints menu to select encoding or decoding
void menu() {
	string msg, encoded_str, decoded_str;
	BTNode<char>* head = new BTNode<char>(' ');
	ifstream rfile("Morse_Code.txt");
	string line;
	
	if (!rfile) {
		cout << "Error: File not found" << endl;
		system("pause");
		return;
	}

	while (getline(rfile, line)) {
		head->tree_builder(line, head);
	}
	rfile.close();
	//prints visualizer for morse code binary tree
	tree_printer(head);

	do {
		main_menu();

		size_t pos;
		string morse;

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
					//replace(encoded_str.begin(), encoded_str.end(), '1', '');
					encoded_str.erase(remove(encoded_str.begin(), encoded_str.end(), '1'), encoded_str.end());
				}
			}//end for loop

			cout << "Message Encoded into Morse Code: " << encoded_str << endl;
			encoded_str = "";
			break;


		case 'd':
			cout << "Enter message to decode: " << endl;
			cin.ignore();
			getline(cin, msg, '\n');

			while ((pos = msg.find(' ')) != string::npos) {
				morse = msg.substr(0, pos);
				decoded_str += decode(morse, 0, head);
				msg.erase(0, pos + 1);
			}
			decoded_str += decode(msg, 0, head);

			cout << "Morse Code Message Decoded: " << decoded_str << endl;
			decoded_str = "";
			break;

		case 'q':
			break;
		}//end of switch

	} while (choice != 'q');
}//end of menu
