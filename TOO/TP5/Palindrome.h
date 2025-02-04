#ifndef  _Palindrome
#define  _Palindrome

#include <array>  
#include <string>
#include <utility> // 'std::pair'

class Palindrome : public std::string {
private:
	// 'constexpr' works with 'static' only...
	// 'constexpr' avoids allocation in compilation unit, i.e., '.cpp' file
	// 'constexpr' allows immediate initialization:
	constexpr static /* const */ std::pair<char, char> _Intervals[] = { std::pair<char, char>('a', 'z'), std::pair<char, char>('A', 'Z') };
public: // Something less than '3' -> compilation "error: excess elements in struct initializer"
	constexpr static /* const */ std::array<char, 3> Special_characters{ ' ', '\n', '\t' };
public:
	Palindrome(const std::string&);
	virtual bool isPalindrome() const;
	const char* toString() const;
};

#endif
