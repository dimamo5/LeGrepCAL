#ifndef KMP_H_
#define KMP_H_

#include "StringSearchAlgorith.h"

using namespace std;

/**
 * @brief Algoritmo de Pesquisa de String Boyer Moore
 *
 */
class kmp: public StringSearchAlgorith {

public:
	kmp(string haystack, string needle);
	/**
	 * Preprocessamento da Needle
	 */
	vector<int> prekmp(string pattern);

	/**
	 * Executa o algoritmo
	 * @return Todas as correspondencias encontradas
	 */
	vector<int> run(bool (*compareFunc)(char, char));
};

#endif /* KMP_H_ */
