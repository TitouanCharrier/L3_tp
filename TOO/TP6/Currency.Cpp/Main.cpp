#include <ctime>
#include <codecvt>
#include <iostream>
#include <locale>

#include "Currency.h"

const Currency &Obsolete_currency::Default_substitute = Euro();

const Currency &Obsolete_currency::substitute() const
{
	return Default_substitute;
}

bool Obsolete_currency::still_active_() const
{
	return false;
}

Currency::Currency(const std::wstring &common_symbol, int iso_code, std::wstring iso_symbol, wchar_t short_symbol) : common_symbol(common_symbol),
																													 iso_code(iso_code),
																													 iso_symbol(iso_symbol),
																													 short_symbol(short_symbol)
{
}

double Currency::rate(const Currency &currency) const
{
	return 1. / currency.to_euro_rate();
}

double Currency::convert_to_dollar(const double amount) const
{
	return amount * to_dollar_rate();
}

double Currency::convert_to_euro(const double amount) const
{
	return amount * to_euro_rate();
}

Euro::Euro() : Currency(L"€", 978, L"EUR", L'€') // 3 bytes required for '€'...
{
}

double Euro::to_dollar_rate() const
{
	return 1. / 1.03; // Oct. 17, 2022 exchange rate
}

double Euro::to_euro_rate() const
{
	return 1.;
}
// Aggregate initialization ('g++ Main.cpp -o Currency -std=c++20' or 'g++ Main.cpp -o Currency -std=c++2a' is required):
const std::tm Lats::_Substitution_date = tm{.tm_mday = 1, .tm_mon = 0, .tm_year = 114};

Lats::Lats() : Currency(L"ℒ𝓈", 428, L"LVL", 'L')
{
}

double Lats::to_dollar_rate() const
{
	const Currency &substitute = this->substitute();
	return rate(*this) * substitute.to_dollar_rate();
}

double Lats::to_euro_rate() const
{
	return 0.702804; // Jan. 1, 2014 exchange rate
}

std::tm Lats::substitution_date() const
{
	return _Substitution_date;
}

Moroccan_dirham::Moroccan_dirham() : Currency(L"درهم", 504, L"MAD", 'M')
{
}

double Moroccan_dirham::to_dollar_rate() const
{
	return 0.091; // Oct. 17, 2022 exchange rate
}

double Moroccan_dirham::to_euro_rate() const
{
	Euro euro;
	return to_dollar_rate() * 1 / euro.to_dollar_rate();
}

int main()
{
	const Euro &euro = (const Euro &)Lats::Default_substitute;
	const Lats &lats = Lats();

	// https://stackoverflow.com/questions/50053386/wcout-does-not-output-as-desired
	// Configure 'std::wcout' to convert the output to UTF-8:
	std::ios_base::sync_with_stdio(false);
	std::locale UTF_8(std::locale(), new std::codecvt_utf8_utf16<wchar_t>);
	std::wcout.imbue(UTF_8); // It associates 'UTF-8' to stream...

	std::wcout << "100" << euro.common_symbol << " -> " << lats.convert_to_euro(100) << lats.common_symbol.c_str() << std::endl;
	std::wcout << "100" << euro.common_symbol << " -> " << euro.convert_to_dollar(100) << '$' << std::endl;
	std::wcout << "100" << lats.common_symbol << " -> " << lats.convert_to_dollar(100) << '$' << std::endl;

	const Moroccan_dirham &moroccan_dirham = Moroccan_dirham();
	std::wcout << moroccan_dirham.convert_to_dollar(1000) << '$' << " -> "
			   << "1000" << moroccan_dirham.common_symbol << std::endl;
	std::wcout << moroccan_dirham.convert_to_euro(1000) << euro.common_symbol << " -> "
			   << "1000" << moroccan_dirham.common_symbol << std::endl;
}
