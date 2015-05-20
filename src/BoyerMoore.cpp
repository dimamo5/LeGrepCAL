/*
 * BoyerMoore.cpp
 *
 *  Created on: 20/05/2015
 *      Author: Utilizador
 */

#include "BoyerMoore.h"

BoyerMoore::BoyerMoore(string haystack, string needle):haystack(haystack),needle(needle) {
	// TODO Auto-generated constructor stub

}

const string& BoyerMoore::getHaystack() const {
	return haystack;
}

const string& BoyerMoore::getNeedle() const {
	return needle;
}

 /**
     * Returns the index within this string of the first occurrence of the
     * specified substring. If it is not a substring, return -1.
     *
     * @param haystack The string to be scanned
     * @param needle The target string to search
     * @return The start index of the substring
     */
 int BoyerMoore::indexOf(string haystack, string needle) {
        if (needle.length() == 0) {
            return 0;
        }
        vector<int> charTable = makeCharTable(needle);
        vector<int> offsetTable = makeOffsetTable(needle);
        for (int i = needle.length() - 1, j; i < haystack.length();) {
            for (j = needle.length() - 1; needle[j] == haystack[i]; --i, --j) {
                if (j == 0) {
                    return i;
                }
            }
            // i += needle.length - j; // For naive method
            i += fmax(offsetTable[needle.length() - 1 - j], charTable[haystack[i]]);
        }
        return -1;
    }

    /**
     * Makes the jump table based on the mismatched character information.
     */
    vector<int> BoyerMoore::makeCharTable(string needle) {
//        final int ;
        vector<int> table(256,needle.length());
//        for (int i = 0; i < table.size(); ++i) {
//            table[i] = needle.length();
//        }
        for (unsigned int i = 0; i < needle.length() - 1; i++) {
            table[needle[i]] = needle.length() - 1 - i;
        }
        return table;
    }

    /**
     * Makes the jump table based on the scan offset which mismatch occurs.
     */
    vector<int> BoyerMoore::makeOffsetTable(string needle) {
        vector<int> table(needle.length());
        int lastPrefixPosition = needle.length();

        for (int i = needle.length() - 1; i >= 0;i--) {
            if (isPrefix(needle, i + 1)) {
                lastPrefixPosition = i + 1;
            }
            table[needle.length() - 1 - i] = lastPrefixPosition - i + needle.length() - 1;
        }
        for (unsigned int i = 0; i < needle.length() - 1; ++i) {
            int slen = suffixLength(needle, i);
            table[slen] = needle.length() - 1 - i + slen;
        }
        return table;
    }

    /**
     * Is needle[p:end] a prefix of needle?
     */
     bool BoyerMoore::isPrefix(string needle, int p) {
        for (unsigned int i = p, j = 0; i < needle.length(); i++, j++) {
            if (needle[i] != needle[j]) {
                return false;
            }
        }
        return true;
    }

    /**
     * Returns the maximum length of the substring ends at p and is a suffix.
     */
    int BoyerMoore::suffixLength(string needle, int p) {
        int len = 0;
        for (int i = p, j = needle.length() - 1;
                 i >= 0 && needle[i] == needle[j]; --i, --j) {
            len += 1;
        }
        return len;
    }
