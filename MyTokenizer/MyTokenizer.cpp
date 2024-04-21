#include <iostream>
#include "Parsers.h"


std::vector<Token> Tokenize(const std::string& input)
{
	std::vector<Token> tokens;
	const size_t size_ = input.size();
	
	std::cout << "Input length: " << size_ << "\n\n";
	
	size_t pos = 0;
	while (pos < size_)
	{
		const auto symbol = static_cast<unsigned char>(input[pos]);
		if (std::isspace(symbol))
		{
			++pos;
		}
		else if (std::isdigit(symbol))
		{
			tokens.emplace_back(ParseNumber(input, pos));
		}
		else if (std::isalpha(symbol))
		{
			tokens.emplace_back(ParseName(input, pos));
		}
		else if (auto it = symbol2Token.find(symbol); it != symbol2Token.end())
		{
			tokens.emplace_back(it->second);
			++pos;
			std::cout << "Added symbol token\t: " << symbol << '\n';
		}
		else
		{
			tokens.emplace_back(UnknownToken{ std::to_string(symbol) });
			std::cout << "Added unknown token\t: " << symbol << '\n';
			++pos;
		}
	}
	return tokens;
}

int main()
{
	// Test
	std::string input = "1 + 2 - 3 * 4 / (abs(5) % sqr(6)) & lala(7)";
	/*std::string input = "";
	std::getline(std::cin, input);*/

	std::vector<Token> tokens = Tokenize(input);
	std::cout << "\nNumber of tokens: " << tokens.size() << '\n';
}