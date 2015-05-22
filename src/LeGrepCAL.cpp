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

	for (int i = 1; i < argc; ++i) {
		string flag(argv[i]);

		if (flag == "-A" && i + 1 <= argc) {
			stringstream(argv[i + 1]) >> temp;

			if (!isdigit(argv[i + 1][0])) {
				cerr << "Argumento " << argv[i + 1] << " n�o � um numero de linha" << endl;
				return 1;
			} else if (linhasDepois <= temp) {
				linhasDepois = temp;
			}
			i++;
		} else if (flag == "-B" && i + 1 <= argc) {
			stringstream(argv[i + 1]) >> temp;

			if (!isdigit(argv[i + 1][0])) {
				cerr << "Argumento " << argv[i + 1] << " n�o � um numero de linha" << endl;
				return 2;
			} else if (linhasAntes <= temp) {
				linhasAntes = temp;
			}
			i++;
		} else if (flag == "-C" && i + 1 < argc) {
			stringstream(argv[i + 1]) >> temp;

			if (!isdigit(argv[i + 1][0])) {
				cerr << "Argumento " << argv[i + 1] << " n�o � um numero de linha" << endl;
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
	ficheiro.open("resources/out.txt");
	string haystack((std::istreambuf_iterator<char>(ficheiro)), (std::istreambuf_iterator<char>()));



	Grep grep(linhasAntes, linhasDepois, false, false, haystack, "Holmes", Grep::NAIVE);
	clock_t begin = clock();
	grep.run();
	clock_t end = clock();
	grep.formatResults();
	cout << grep.getResult();


	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << "Tempo" << elapsed_secs << endl;

	return 0;
}

