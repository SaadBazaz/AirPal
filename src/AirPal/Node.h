#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "Vector.h"
using namespace std;

class Node {
public:
	string meaning;
	Vector <string> synonyms;
	Node* alphabetArray[26];
	long key;
	Vector<string> dads;

	Node() {
		for (int i = 0; i < 26; i++) {
			alphabetArray[i] = nullptr;
		}

		//===============FOR DEBUGGING===============//
		//cout << "Set the alphabet array of "<<this<<" to nullptr." << endl;
		//===============FOR DEBUGGING===============//

		key = time(NULL);
		meaning = "";

	}

	Node(int index) {
		for (int i = 0; i < 26; i++) {
			if (i == index)
				alphabetArray[i] = new Node;
			else
				alphabetArray[i] = nullptr;
		}

		//===============FOR DEBUGGING===============//
		//cout << "Set the alphabet array to nullptr." << endl;
		//===============FOR DEBUGGING===============//

		meaning = "";
		key = time(NULL);
	}



	Node(string Meaning, Vector <string> Synonyms) {
		for (int i = 0; i < 26; i++) {
			alphabetArray[i] = nullptr;
		}
		meaning = Meaning;
		synonyms = Synonyms;
		key = time(NULL);
	}

	bool clearProperties() {
		meaning = "";
		synonyms.clear();
		for (int i = 0; i < 26; i++) {
			if (alphabetArray[i] != nullptr)
				return false;
		}
		return true;
	}

	bool isCursorWord() {
		return meaning != "";
	}

	void setCharacter(char index) {
		if (index <= 'Z' && index >= 'A') {
			index -= 'A';
		}
		else if (index <= 'z' && index >= 'a') {
			index -= 'a';
		}
		else
			throw invalid_argument("Index is less than or greater than the alphabet!");

		//===============FOR DEBUGGING===============//
		//cout << "Index is " << (int)index << endl;
		//===============FOR DEBUGGING===============//

		alphabetArray[(int)index] = new Node;

		//===============FOR DEBUGGING===============//
		//cout << "Created at " << alphabetArray[(int)index] << endl;
		//===============FOR DEBUGGING===============//
	}

	Node*& moveToAlphabet(char index) {
		if (index <= 'Z' && index >= 'A') {
			index -= 'A';
		}
		else if (index <= 'z' && index >= 'a') {
			index -= 'a';
		}
		else if (index > 25 || index < 0)
			throw invalid_argument("Index is less than or greater than the alphabet!");
		//cout << "Address inside moveToAlphabet... " << alphabetArray[(int)index] << endl;
		if (alphabetArray[(int)index] == nullptr)
			throw logic_error("Cannot move as the Node is nullptr.");
		return alphabetArray[(int)index];
	}

	bool isAlphabetNull(char index) {
		if (index <= 'Z' && index >= 'A') {
			index -= 'A';
		}
		else if (index <= 'z' && index >= 'a') {
			index -= 'a';
		}
		else if (index > 25 || index < 0)
			throw invalid_argument("Index is less than or greater than the alphabet!");

		//===============FOR DEBUGGING===============//
		//cout << "Is the alphabet null? ";
		//===============FOR DEBUGGING===============//

		return alphabetArray[(int)index] == nullptr;
	}

	void setMeaning(string Meaning) {
		meaning = Meaning;

		//===============FOR DEBUGGING===============//
		//cout << "Set meaning to '" << meaning << "'." << endl;
		//===============FOR DEBUGGING===============//

	}

	void setKey() {
		key = time(NULL);
	}

	void addSynonym(string synonym) {
		synonyms.push_back(synonym);

		//===============FOR DEBUGGING===============//
		//cout << "Added synonym '" << synonym << "'." << endl;
		//===============FOR DEBUGGING===============//

	}

	void addDad(string dad) {
		dads.push_back(dad);
	}


	bool isNull() {
		return meaning == "";
	}


	~Node() {
		for (int i = 0; i < 26; i++) {
			if (alphabetArray[i] != nullptr)
				delete alphabetArray[i];
		}
	}
};
