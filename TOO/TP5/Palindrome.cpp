#include <cctype> // 'std::tolower'
#include <iterator> // C++17: 'std::size'
#include <string> // 'std::string'
#include <utility> // 'std::pair'

#include "Palindrome.h"

Palindrome::Palindrome(const std::string& string) {
	for (char c : string) { // For each character in the source string
		for (unsigned j = 0; j < std::size(_Intervals); ++j) { // C++17
			if (c >= _Intervals[j].first && c <= _Intervals[j].second) { // The character belongs to the authorized intervals
				this->push_back(c); // Character is valid and thus added to the palindrome
				break; // Quit the 'for' loop on 'j'
			}
		}
	}
}

bool Palindrome::isPalindrome() const {
	for (unsigned i = 0; i < this->length() / 2; ++i) { // For each character in the palindrome (up to half of the palindrome's length)
		// 'std::tolower': 'A' -> 'a'
		if (std::tolower(this->operator[](i)) != std::tolower(this->operator[](this->length() - 1 - i)))
			return false;
	}
	return true;
}

const char* Palindrome::toString() const {
	return this->data(); // Content of a string as 'const char*' for compatibility with the C programming language...
}
