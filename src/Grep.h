/*
 * Grep.h
 *
 *  Created on: 21/05/2015
 *      Author: Utilizador
 */

#ifndef GREP_H_
#define GREP_H_

#include <string>
#include "StringSearchAlgorith.h"
#include "BoyerMoore.h"
#include "Naive.h"
#include "KMP.h"

using namespace std;

class Grep {
private:
	unsigned int linhasAntes = 1, linhasDepois = 1;
	bool ignoreCase = false, invertMatch = false;

	string haystack, needle, result;

	vector<int> resultados;

	StringSearchAlgorith *algoritmo = NULL;

public:
	enum SSA {
		BOYER_MOORE, NAIVE, KMP
	};

	Grep(int la, int ld, bool ic, bool im, string haystack, string needle, SSA algoritmo);

	Grep(string haystack, string needle, SSA algoritmo);

	void run();

	void formatResults();

	string getResult();

	void changeAlgoritmo(SSA novoAlgoritmo);

	//Funcoes de Comparação

	static bool compareCaseSensative(char c1, char c2);

	static bool compareCaseInsensative(char c1, char c2);
};

#endif /* GREP_H_ */
