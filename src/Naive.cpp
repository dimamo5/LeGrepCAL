/*
 * Naive.cpp
 *
 *  Created on: 21/05/2015
 *      Author: Utilizador
 */

#include "Naive.h"
#include <iostream>
#include "StringSearchAlgorith.h"

Naive::Naive(string haystack, string needle) :
		StringSearchAlgorith(haystack, needle) {

}

vector<int> Naive::run(bool (*compareFunc)(char, char)) {
	vector<int> resultados;
	for (unsigned int i = 0; i < haystack.length(); i++) {
		for (unsigned int j = 0; j < needle.length(); j++) {
			if (!compareFunc(haystack[i + j], needle[j])) {
				break;
			} else if (j == needle.length() - 1) {
				resultados.push_back(i);
			}
		}
	}
	return resultados;
}
