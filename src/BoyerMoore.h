/*
 * BoyerMoore.h
 *
 *  Created on: 20/05/2015
 *      Author: Utilizador
 */

#ifndef BOYERMOORE_H_
#define BOYERMOORE_H_

#include <string>
#include <vector>

#include "StringSearchAlgorith.h"

using namespace std;

/**
 * @brief Algoritmo de Pesquisa de String Boyer Moore
 *
 */
class BoyerMoore: public StringSearchAlgorith {
private:

	int const ALPHABET_SIZE = 256;
	vector<int> charTable;
	vector<int> offsetTable;

	vector<int> makeCharTable();
	vector<int> makeOffsetTable();
	bool isPrefix(string needle, int p);
	int suffixLength(string needle, int p);

public:
	BoyerMoore(string haystack, string needle);
	/**
	 * Executa o Algoritmo
	 * @return Retorna apenas a primeira corespondencia encontrada
	 */
	int indexOfFirst();
	/**
	 * Executa o Algoritmo
	 * @return Todas as correspondencias encontradas
	 */
	vector<int> run(bool (*compareFunc)(char, char));
};

#endif /* BOYERMOORE_H_ */
