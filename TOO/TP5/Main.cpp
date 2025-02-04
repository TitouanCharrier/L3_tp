#include <iostream>
#include <stdexcept>

#include "Palindrome.h"

int main(int argc, char** argv) {

	int out_of_bounds = Palindrome::Special_characters.size();
	// std::cout << Palindrome::Special_characters[out_of_bounds] << '\n'; // Out of bounds (no control)...
	try {
		std::cout << Palindrome::Special_characters.at(out_of_bounds) << '\n'; // Out of bounds (control)...
	}
	catch (std::logic_error & le) { // Inheritance graph: 'std::exception' < 'std::logic_error' < 'std::out_of_range'
		std::cerr << typeid (le).name() << ", " << le.what() << ": " << out_of_bounds << '\n';
	}

	Palindrome p1("Elu par cette crapule"); // French
	Palindrome p2("Esope reste ici et se repose"); // French
	Palindrome p3("Was it a car or a cat I saw?"); // English
	Palindrome p4("This is not a palindrome"); // English

	std::cout << p1.toString() << ": " << (p1.isPalindrome() ? "true" : "false") << '\n'; // 'true'
	std::cout << p2.toString() << ": " << (p2.isPalindrome() ? "true" : "false") << '\n'; // 'true'
	std::cout << p3.toString() << ": " << (p3.isPalindrome() ? "true" : "false") << '\n'; // 'true'
	std::cout << p4.toString() << ": " << (p4.isPalindrome() ? "true" : "false") << '\n'; // 'false'

	return 0;
}

