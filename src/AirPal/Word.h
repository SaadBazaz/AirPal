#pragma once
#include <string>
#include "Vector.h"
using namespace std;

//--------- NUMBERING FOR REFERENCE ---------
//#define A 0
//#define B 1
//#define C 2
//#define D 3
//#define E 4
//#define F 5
//#define G 6
//#define H 7
//#define I 8
//#define J 9
//#define K 10
//#define L 11
//#define M 12
//#define N 13
//#define O 14
//#define P 15
//#define Q 16
//#define R 17
//#define S 18
//#define T 19
//#define U 20
//#define V 21
//#define W 22
//#define X 23
//#define Y 24
//#define Z 25


class Word {
public:
	string word;
	string meaning;
	Vector <string> synonyms;


	Word(string theWord) :word(theWord), meaning("") {

	}

	Word(string theWord, string theMeaning, Vector <string> theSynonyms) :word(theWord), meaning(theMeaning) {
		synonyms = theSynonyms;
	}
};