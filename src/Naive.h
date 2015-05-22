/*
 * Naive.h
 *
 *  Created on: 21/05/2015
 *      Author: Utilizador
 */

#ifndef NAIVE_H_
#define NAIVE_H_

#include <string>
#include <vector>

#include "StringSearchAlgorith.h"

using namespace std;

class Naive: public StringSearchAlgorith {
public:
	Naive(string haystack, string needle);

	vector<int> run();
};

#endif /* NAIVE_H_ */
