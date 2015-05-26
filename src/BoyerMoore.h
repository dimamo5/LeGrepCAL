/*
 * BoyerMoore.h
 *
 *  Created on: 20/05/2015
 *      Author: Utilizador
 */

#ifndef BOYERMOORE_H_
#define BOYERMOORE_H_

#include <string>
#include <vector>
#include <cmath>

#include "StringSearchAlgorith.h"

using namespace std;

class BoyerMoore: public StringSearchAlgorith {
private:

	int const ALPHABET_SIZE = 256;
	vector<int> charTable;
	vector<int> offsetTable;

	vector<int> makeCharTable();
	vector<int> makeOffsetTable();
	bool isPrefix(string needle, int p);
	int suffixLength(string needle, int p);

public:
	BoyerMoore(string haystack, string needle);
	int indexOfFirst();
	vector<int> run(bool (*compareFunc)(char, char));
};

#endif /* BOYERMOORE_H_ */
