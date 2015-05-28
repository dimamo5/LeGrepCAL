#ifndef KMP_H_
#define KMP_H_

#include "StringSearchAlgorith.h"

using namespace std;

class kmp: public StringSearchAlgorith {

public:
	kmp(string haystack, string needle);
	vector<int> prekmp(string pattern);
	vector<int> run(bool (*compareFunc)(char, char));
};

#endif /* KMP_H_ */
