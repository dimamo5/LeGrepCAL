//============================================================================
// Name        : LeGrepCAL.cpp
// Author      : Diogo Moura
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <cctype>
#include "Grep.h"
using namespace std;

int main(int argc, char* argv[]) {
	cout << "Grep" << endl;

	int linhasAntes = 1, linhasDepois = 1, temp;
	bool invertMatch = false, ignoreCase = false;

	for (int i = 1; i < argc; ++i) {
		string flag(argv[i]);
		//TODO Falta flags alternativas para cada tipo

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
		} else if (flag.compare(0, 16, "--after-context=") == 0) {
			stringstream(flag.substr(16, flag.length())) >> temp;
			if (temp >= 99) {
				cerr << "Numero Linhas exagerado " << endl;
				return 0;
			} else {
				if (linhasDepois < temp) {
					linhasDepois = temp;
				}
			}
		} else if (flag.compare(0, 17, "--before-context=") == 0) {
			stringstream(flag.substr(17, flag.length())) >> temp;
			if (temp >= 99) {
				cerr << "Numero Linhas exagerado " << endl;
				return 0;
			} else {
				if (linhasAntes < temp) {
					linhasAntes = temp;
				}
			}
		} else if (flag.compare(0, 10, "--context=") == 0) {
			stringstream(flag.substr(10, flag.length())) >> temp;
			if (temp >= 99) {
				cerr << "Numero Linhas exagerado " << endl;
				return 0;
			} else {
				if (linhasAntes < temp) {
					linhasAntes = temp;
				}
				if (linhasDepois < temp) {
					linhasDepois = temp;
				}
			}
		} else if (flag == "--ignore-case") {
			ignoreCase = true;
		} else if (flag == "--invert-match") {
			invertMatch = true;
		}

		else {
			cerr << "Argumentos incorrectos!!!" << endl;
		}
	}

	cout << "Linhas Antes: " << linhasAntes << "\t Linhas Depois: " << linhasDepois << "\t Case Sensative: " << ignoreCase << "\t Invert Match: " << invertMatch
			<< endl;

	ifstream ficheiro;
	ficheiro.open("resources/out.txt");
	string haystack((std::istreambuf_iterator<char>(ficheiro)), (std::istreambuf_iterator<char>()));

	cout << "Tamanho Haystack:" << haystack.length() << endl;

	Grep grep(linhasAntes, linhasDepois, ignoreCase, invertMatch, haystack, "Sherlock Holmes", Grep::BOYER_MOORE);
	clock_t begin = clock();
	grep.run();
	clock_t end = clock();

	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << "Tempo Pesquisa" << elapsed_secs << endl;

	begin = clock();
	grep.formatResults();
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Tempo Reorganização de Output" << elapsed_secs << endl << endl;

	cout << grep.getResult() << endl;

	return 0;
}

// First 4 bits are background, last 4 bits are foreground
void cor(int background, int foreground) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, foreground + 16 * background);
}

