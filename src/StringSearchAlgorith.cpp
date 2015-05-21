/*
 * StringSearchAlgorith.cpp
 *
 *  Created on: 21/05/2015
 *      Author: Utilizador
 */

#include "StringSearchAlgorith.h"

StringSearchAlgorith::StringSearchAlgorith(string haystack, string needle) :
		haystack(haystack), needle(needle) {

}

StringSearchAlgorith::StringSearchAlgorith() {

}

string StringSearchAlgorith::getHaystack() const {
	return haystack;
}

string StringSearchAlgorith::getNeedle() const {
	return needle;
}
