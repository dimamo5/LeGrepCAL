//============================================================================
// Name        : LeGrepCAL.cpp
// Author      : Diogo Moura
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include "BoyerMoore.h"
using namespace std;

int main(int argc, char* argv[]) {
	cout << "BoyerMoore" << endl; // prints !!!Hello World!!!

	int linhasAntes = 1, linhasDepois = 1, temp;

	for (int i = 1; i < argc; ++i) {
		string flag(argv[i]);
		cout<<argc<<endl;
		if (flag == "-A" && argc > 2) {
			cout<<"entra";
			if (stringstream(argv[i + 1]) >> temp) {
				if (isdigit(temp)) {
					cerr << "Argumento " << argv[i + 1] << "não é um numero de linha";
				} else if (linhasAntes > temp) {
					linhasAntes = temp;
				}
			}

		} else if (flag == "-B" && argc > 2) {
			if (stringstream(argv[i + 1]) >> temp) {
				if (isdigit(temp)) {
					cerr << "Argumento " << argv[i + 1] << "não é um numero de linha";
				} else if (linhasAntes > temp) {
					linhasDepois = temp;
				}
			}

		}
		if (flag == "-C" && argc > 2) {
			if (stringstream(argv[i + 1]) >> temp) {
				if (isdigit(temp)) {
					cerr << "Argumento " << argv[i + 1] << "não é um numero de linha";
				} else if (linhasAntes > temp) {
					linhasDepois = temp;
				}
			}

		}
	}

	ifstream ficheiro;
	ficheiro.open("resources/1.txt");
	string haystack((std::istreambuf_iterator<char>(ficheiro)), (std::istreambuf_iterator<char>()));

	//cout << haystack << endl;

	BoyerMoore teste(haystack, "name");

	vector<int> resultados = teste.indexOfAll(teste.getHaystack(), teste.getNeedle());
	cout << "nr de resultados:" << resultados.size() << endl;
	cout << "resultados:" << resultados[0] << endl;

	for (int i = 0; i < resultados.size(); i++) {
		cout << haystack[resultados[i]] << haystack[resultados[i] + 1] << haystack[resultados[i] + 2] << haystack[resultados[i] + 3] << endl;
	}

	return 0;
}

