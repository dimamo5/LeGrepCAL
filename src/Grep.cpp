/*
 * Grep.cpp
 *
 *  Created on: 21/05/2015
 *      Author: Utilizador
 */

#include "Grep.h"
#include <iostream>

Grep::Grep(int la, int ld, bool ic, bool im, string haystack, string needle, SSA algoritmo) :
		linhasAntes(la), linhasDepois(ld), ignoreCase(ic), invertMatch(im), haystack(haystack), needle(needle) {
	if (algoritmo == BOYER_MOORE) {
		this->algoritmo = new BoyerMoore(haystack, needle);
	} else if (algoritmo == NAIVE) {
		this->algoritmo = new Naive(haystack, needle);
	}
}

Grep::Grep(string haystack, string needle, SSA algoritmo) {

}

void Grep::run() {
	resultados = algoritmo->run();
}

void Grep::formatResults() {

	unsigned int j, ite;
	char lastChar = '\0';

	string resultados_temp;

	for (unsigned int i = 0; i < resultados.size(); i++) {
		j = 0;
		ite = resultados[i];

		while (j < linhasAntes) {
			if (haystack[ite] == '\n' && lastChar != '\n') {
				j++;
			}
			resultados_temp = haystack[ite] + resultados_temp;
			lastChar = haystack[ite];
			ite--;
		}

		j = 0;

		ite = resultados[i] + 1;

		while (j < linhasDepois) {
			if (haystack[ite] == '\n' && lastChar != '\n') {
				j++;
			}
			resultados_temp = resultados_temp + haystack[ite];
			lastChar = haystack[ite];
			ite++;
		}

		resultados_temp += "--------";
		result += resultados_temp;
		resultados_temp.clear();
	}
	result+='\n';

}

string Grep::getResult() {
	return result;
}

void Grep::changeAlgoritmo(SSA novoAlgoritmo) {
	if (this->algoritmo != NULL) {
		delete (this->algoritmo);

		if (novoAlgoritmo == BOYER_MOORE) {
			this->algoritmo = new BoyerMoore(haystack, needle);
		} else if (novoAlgoritmo == NAIVE) {
			this->algoritmo = new Naive(haystack, needle);
		}
	}
}
