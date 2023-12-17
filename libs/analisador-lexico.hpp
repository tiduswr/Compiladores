#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <vector>
#include <cctype>
#include <queue>
#include "token.hpp"

class Lexer {
    public:
        Lexer(const std::string& source_code);
        Token getNextToken();
        std::vector<Token>* getTokens();

    private:
        std::vector<Token> tokens;
        std::size_t tokenIndex;
        std::string source_code;

        std::string bufferToString(std::queue<char>& buffer);
        void mkToken(const std::string& tk, TokenType t);
};

#endif
