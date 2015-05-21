/*
 * StringSearchAlgorith.h
 *
 *  Created on: 21/05/2015
 *      Author: Utilizador
 */

#ifndef STRINGSEARCHALGORITH_H_
#define STRINGSEARCHALGORITH_H_

#include <string>
#include <vector>

using namespace std;

class StringSearchAlgorith {
protected:
	string haystack;
	string needle;

public:
	StringSearchAlgorith();
	StringSearchAlgorith(string haystack, string needle);

	virtual vector<int> run() = 0; //funtao que tem de ser implementada pelas classes derivadas

	string getHaystack() const;
	string getNeedle() const;
};

#endif /* STRINGSEARCHALGORITH_H_ */
