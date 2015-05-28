#include "KMP.h"
#include <iostream>
#include <stdlib.h>

kmp::kmp(string haystack, string needle) :
		StringSearchAlgorith(haystack, needle) {
}

vector<int> kmp::prekmp(string pattern) {

	int m = pattern.length(), k = 0;
	vector<int> f(m);
	f[0] = 0;

//	for (int i=1; i < m; i++) {
//		while (k > 0 && pattern[k] != pattern[i]) {
//			k = f[k-1];
//		}
//		if (pattern[k] == pattern[i]) {
//			k++;
//		}
//		f[i] = k;
//	}

	for (int i = 1; i < pattern.length(); i++) {
		// Start by assuming we're extending the previous LSP
		int j = f[i - 1];
		while (j > 0 && pattern[i] != pattern[j])
			j = f[j - 1];
		if (pattern[i] == pattern[j])
			j++;
		f[i] = j;
	}
	return f;
}

vector<int> kmp::run(bool (*compareFunc)(char, char)) {

	int m = needle.length();
	int n = haystack.length();
	vector<int> f, results;

	f = prekmp(needle);   //preprocessa tabela de prefixos/sufixos

	int j = 0;
	for (int i = 0; i < n; i++) {
		while (j > 0 && haystack[i] != needle[j]) {
			// Fall back in the pattern
			j = f[j - 1];
		}
		if (haystack[i] == needle[j]) {
			j++;
			if (j == m)
				results.push_back(i - (j - 1));
		}
	}

	return results;
}

