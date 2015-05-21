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
	cout << "BoyerMoore" << endl;

	int linhasAntes = 1, linhasDepois = 1, temp;

	for (int i = 1; i < argc; ++i) {
		string flag(argv[i]);

		if (flag == "-A" && i + 1 <= argc) {
			stringstream(argv[i + 1]) >> temp;

			if (!isdigit(argv[i + 1][0])) {
				cerr << "Argumento " << argv[i + 1] << " não é um numero de linha" << endl;
				return 1;
			} else if (linhasAntes <= temp) {
				linhasAntes = temp;
			}
			i++;
		} else if (flag == "-B" && i + 1 <= argc) {
			stringstream(argv[i + 1]) >> temp;

			if (!isdigit(argv[i + 1][0])) {
				cerr << "Argumento " << argv[i + 1] << " não é um numero de linha" << endl;
				return 2;
			} else if (linhasAntes <= temp) {
				linhasDepois = temp;
			}
			i++;
		} else if (flag == "-C" && i + 1 < argc) {
			stringstream(argv[i + 1]) >> temp;

			if (!isdigit(argv[i + 1][0])) {
				cerr << "Argumento " << argv[i + 1] << " não é um numero de linha" << endl;
				return 3;
			} else if (linhasAntes <= temp && linhasDepois <= temp) {
				linhasDepois = temp;
				linhasAntes = temp;
			}
			i++;
		} else {
			cerr << "Argumentos incorrectos!!!" << endl;
		}

	}

	cout << "Linhas Antes: " << linhasAntes << "\t Linhas Depois: " << linhasDepois << endl;

	ifstream ficheiro;
	ficheiro.open("resources/1.txt");
	string haystack((std::istreambuf_iterator<char>(ficheiro)), (std::istreambuf_iterator<char>()));

	//cout << haystack << endl;

	BoyerMoore teste(haystack, "Sherlock");

	vector<int> resultados = teste.indexOfAll(teste.getHaystack(), teste.getNeedle());
	cout << "nr de resultados:" << resultados.size() << endl;
	cout << "resultados:" << resultados[0] << endl;

	for (int i = 0; i < resultados.size(); i++) {
		cout << haystack[resultados[i]] << haystack[resultados[i] + 1] << haystack[resultados[i] + 2] << haystack[resultados[i] + 3] << endl;
	}

	return 0;
}

