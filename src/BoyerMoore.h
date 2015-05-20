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

using namespace std;

class BoyerMoore {
private:

	int const ALPHABET_SIZE = 256;
	string haystack;
	string needle;
	vector<int> charTable;
	vector<int> offsetTable;

	vector<int> makeCharTable(string needle);
	vector<int> makeOffsetTable(string needle);
	bool isPrefix(string needle, int p);
	int suffixLength(string needle, int p);

public:
	BoyerMoore(string haystack, string needle);
	int indexOf(string haystack, string needle);
	vector<int> indexOfAll(string haystack, string needle);
	const string& getHaystack() const;
	const string& getNeedle() const;
};

#endif /* BOYERMOORE_H_ */
