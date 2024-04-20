#pragma once

#include <variant>
#include <string>
#include <unordered_map>


struct OpeningBracket {};
struct ClosingBracket {};


struct MinToken {};     
struct MaxToken {};     
struct AbsToken {};     
struct SqrToken {};     


struct Plus     {};
struct Minus    {};
struct Multiply {};
struct Divide   {};
struct Modulo   {};


struct Number       { int value; };
struct UnknownToken { std::string name; };


using Token = std::variant<OpeningBracket, ClosingBracket, 
                           MinToken, MaxToken, AbsToken, SqrToken,
                           Plus, Minus, Multiply, Divide, Modulo,
                           Number, UnknownToken>;


const std::unordered_map<unsigned char, Token> symbol2Token{ 
                           {'(', OpeningBracket{}}, {')', ClosingBracket{}},
                           {'+', Plus{}}, {'-', Minus{}}, {'*', Multiply{}}, {'/', Divide{}}, {'%', Modulo{}},
};

const std::unordered_map<std::string, Token> name2Token{
                           {"min", MinToken{}}, {"max", MaxToken{}}, {"abs", AbsToken{}}, {"sqr", SqrToken{}},
};