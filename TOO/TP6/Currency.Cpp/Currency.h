#include <ctime>

#include <string>

class Currency;

class Obsolete_currency
{
public:
	static const Currency &Default_substitute;
	const Currency &substitute() const;
	bool still_active_() const;
	// Alternative C++ time management: https://en.cppreference.com/w/cpp/chrono
	virtual std::tm substitution_date() const = 0;
};

class Currency
{
public:
	// 'std::wstring' <=> 'std::basic_string<wstring>':
	const std::wstring common_symbol; // L"$" <- american dollar
	const int iso_code;				  // 840 <- american dollar
	const std::wstring iso_symbol;	  // L"USD" <- american dollar
	// 'wchar_t' is 2-byte long:
	const wchar_t short_symbol; // L'$'
protected:
	Currency(const std::wstring &, int, std::wstring, wchar_t = L'$');

public:
	double rate(const Currency &) const;
	virtual double to_dollar_rate() const = 0;
	double convert_to_dollar(const double amount) const;
	virtual double to_euro_rate() const = 0;
	double convert_to_euro(const double amount) const;
};

class Euro : public Currency
{
public:
	Euro();
	double to_dollar_rate() const;
	double to_euro_rate() const;
};

class Lats : public Currency, public Obsolete_currency
{ /** Letonia currency replaced by Euro January, 1st 2014 **/
private:
	static const std::tm _Substitution_date;

public:
	Lats();
	double to_dollar_rate() const;
	double to_euro_rate() const;
	std::tm substitution_date() const;
};

class Moroccan_dirham : public Currency
{
public:
	Moroccan_dirham();
	double to_dollar_rate() const;
	double to_euro_rate() const;
};