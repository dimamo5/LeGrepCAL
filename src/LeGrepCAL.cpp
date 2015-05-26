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
#include <ctime>
#include <sstream>
#include <cctype>
#include "Grep.h"
using namespace std;

int main(int argc, char* argv[]) {
	cout << "BoyerMoore" << endl;

	int linhasAntes = 1, linhasDepois = 1, temp;
	bool invertMatch = false, ignoreCase = false;

	for (int i = 1; i < argc; ++i) {
		string flag(argv[i]);

		if (flag == "-A" && i + 1 <= argc) {
			stringstream(argv[i + 1]) >> temp;

			if (!isdigit(argv[i + 1][0])) {
				cerr << "Argumento " << argv[i + 1] << " não é um numero de linha" << endl;
				return 1;
			} else if (linhasDepois <= temp) {
				linhasDepois = temp;
			}
			i++;
		} else if (flag == "-B" && i + 1 <= argc) {
			stringstream(argv[i + 1]) >> temp;

			if (!isdigit(argv[i + 1][0])) {
				cerr << "Argumento " << argv[i + 1] << " não é um numero de linha" << endl;
				return 2;
			} else if (linhasAntes <= temp) {
				linhasAntes = temp;
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
		} else if (flag == "-i") {
			ignoreCase = true;

		} else if (flag == "-v") {
			invertMatch = true;
		} else {
			cerr << "Argumentos incorrectos!!!" << endl;
		}
	}

	cout << "Linhas Antes: " << linhasAntes << "\t Linhas Depois: " << linhasDepois << "\t Case Sensative: " << ignoreCase << "\t Invert Match: " << invertMatch
			<< endl;

	ifstream ficheiro;
	ficheiro.open("resources/1.txt");
	string haystack((std::istreambuf_iterator<char>(ficheiro)), (std::istreambuf_iterator<char>()));

	cout << "Tamanho:" << haystack.length() << endl;

	Grep grep(linhasAntes, linhasDepois, ignoreCase, invertMatch, haystack, "mention her under any other name", Grep::BOYER_MOORE);
	clock_t begin = clock();
	grep.run();
	clock_t end = clock();
	grep.formatResults();
	cout << grep.getResult()<<endl;

	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << "Tempo" << elapsed_secs << endl;

	return 0;
}

