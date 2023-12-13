#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "token.hpp"

class Lexer {
public:
    Lexer(const std::string& source_code);
    Token getNextToken();

private:
    std::vector<Token> tokens;
    size_t tokenIndex;
    size_t current_position;
    size_t source_size;
    const char* source_code;

    void mkToken(const std::string& tk, TokenType t);
    char lookAhead();
    void match(const char& token);
    void digit();  
    void number();  
    void op();
    void paren_e();
    void paren_d();
    void expr();
    void expr_tail();
    void term();
    void term_tail();
    void factor();
};

#endif
