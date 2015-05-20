//============================================================================
// Name        : LeGrepCAL.cpp
// Author      : Diogo Moura
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "BoyerMoore.h"
using namespace std;

int main() {
	cout << "BoyerMoore" << endl; // prints !!!Hello World!!!

	ifstream ficheiro;
	ficheiro.open("resources/1.txt");
	string haystack((std::istreambuf_iterator<char>(ficheiro)), (std::istreambuf_iterator<char>()));

	cout << haystack << endl;

	BoyerMoore teste(haystack, "Name");

	cout << "Index:" << teste.indexOf(teste.getHaystack(), teste.getNeedle());
	cout<<haystack[135]<<haystack[136]<<haystack[137]<<haystack[138];

	return 0;
}

