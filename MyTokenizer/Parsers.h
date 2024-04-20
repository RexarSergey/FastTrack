#pragma once

#include "Tokens.h"


int ToDigit(unsigned char symbol)
{
	return symbol - '0';
}

Number ParseNumber(const std::string& input, size_t& pos)
{
	int value = 0;
	auto symbol = static_cast<unsigned char>(input[pos]);
	while (std::isdigit(symbol))
	{
		value = value * 10 + ToDigit(symbol);
		if (pos == input.size() - 1)
		{
			++pos;
			break;
		}
		symbol = static_cast<unsigned char>(input[++pos]);
	}
	std::cout << "Added number token\t: " << value << '\n';
	return Number{ value };
}

Token ParseName(const std::string& input, size_t& pos)
{
	std::string str = "";
	auto symbol = static_cast<unsigned char>(input[pos]);
	while (std::isalpha(symbol))
	{
		str += symbol;
		if (pos == input.size() - 1)
		{
			++pos;
			break;
		}
		symbol = static_cast<unsigned char>(input[++pos]);
	}

	if (auto it = name2Token.find(str); it != name2Token.end())
	{
		std::cout << "Added name token\t: " << str << '\n';
		return it->second;
	}

	std::cout << "Added unknown token\t: " << str << '\n';
	return UnknownToken{ str };
}