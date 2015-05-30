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

/**
 * @brief Class Com toda a informacao para executar o grep
 * Haystack - Buffer com texto a ser pesquisado
 * Needle - Palavra(s) a pesquisar na Haystack
 * Result - Buffer com o resultado já formatado consoante as flag
 * algoritmo - Algoritmo a ser utilizado na pesquisa
 *
 */
class Grep {
private:
	unsigned int linhasAntes = 1, linhasDepois = 1;
	bool ignoreCase = false, invertMatch = false;

	double tempoPesquisa;

	string haystack, needle, result;

	vector<int> resultados;

	StringSearchAlgorith *algoritmo = NULL;

public:
	enum SSA {
		BOYER_MOORE, NAIVE, KMP
	};

	/**
	 * Construtor utilizado flags
	 */
	Grep(int la, int ld, bool ic, bool im, string haystack, string needle, SSA algoritmo);

	/**
	 * Construtor sem as flags
	 */
	Grep(string haystack, string needle, SSA algoritmo);

	/**
	 * Funcoa que executa o algoritmo de pesquisa
	 */
	void run();

	/**
	 * Formata o buffer resultados consoante as flags utilizadas
	 */
	void formatResults();

	string getResult();

	/**
	 * Muda o algoritmo de pesquisa
	 */
	void changeAlgoritmo(SSA novoAlgoritmo);

	double getTempoPesquisa();

	//Funcoes de Comparação

	/**
	 * Funcao de comparacao para pesquisa sensivel a Maiusculas/Minusculas
	 */
	static bool compareCaseSensative(char c1, char c2);

	/**
	 * Funcao de comparacao para pesquisa insensivel a Maiusculas/Minusculas
	 */
	static bool compareCaseInsensative(char c1, char c2);
};

#endif /* GREP_H_ */
