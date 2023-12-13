#include <iostream>
#include <vector>
#include <set>
#include <cctype>
#include <algorithm>
#include "token.hpp"
#include "analisador-lexico.hpp"

Lexer::Lexer(const std::string& source_code) {
    this->source_code = source_code.c_str();
    this->source_size = source_code.size();
    current_position = 0;
    expr();
}

char Lexer::lookAhead(){
    return source_code[current_position];
}

void Lexer::mkToken(const std::string& tk, TokenType t){
    Token token;
    token.tipo = t;
    token.valor = tk;
    tokens.push_back(token);
}

Token Lexer::getNextToken() {
    if (tokenIndex < tokens.size()) {
        return tokens[tokenIndex++];
    } else {
        Token end;
        end.tipo = FIM;
        end.valor = "";
        return end;
    }
}

void Lexer::match(const char& token){
    if(lookAhead() == token && (current_position < source_size)){
        current_position++;
    }else{
        throw TokenInvalidError(current_position);
    }
}

void Lexer::paren_e(){
    if(lookAhead() == '('){
        mkToken(std::string(1, lookAhead()), T_PAR_ESQ); match(lookAhead());
    }else{
        throw TokenInvalidError(current_position);
    }
}

void Lexer::paren_d(){
    if(lookAhead() == ')'){
        mkToken(std::string(1, lookAhead()), T_PAR_DIR); match(lookAhead());
    }else{
        throw TokenInvalidError(current_position);
    }
}

void Lexer::op(){
    switch (lookAhead()){
        case '+':
            mkToken(std::string(1, lookAhead()), OP_MAIS); match(lookAhead());
            break;
        case '-':
            mkToken(std::string(1, lookAhead()), OP_MENOS); match(lookAhead());
            break;
        case '*':
            mkToken(std::string(1, lookAhead()), OP_MULT); match(lookAhead());
            break;
        case '/':
            mkToken(std::string(1, lookAhead()), OP_DIV); match(lookAhead());
            break;
        default:
            throw TokenInvalidError(current_position);
            break;
    }
}

void Lexer::expr(){
    term(); expr_tail();
}

void Lexer::expr_tail(){
    switch (lookAhead()){
        case '+':
            op(); term(); expr_tail();
            break;
        case '-':
            op(); term(); expr_tail();
            break;
        default:
            break;
    }
}

void Lexer::term(){
    factor(); term_tail();
}

void Lexer::term_tail(){
    switch (lookAhead()){
        case '*':
            op(); factor(); term_tail();
            break;
        case '/':
            op(); factor(); term_tail();
            break;
        default:
            break;
    }
}

void Lexer::digit() {
    std::string buffer = "";
    while (isdigit(lookAhead())) {
        buffer = buffer + std::string(1, lookAhead());
        match(lookAhead());
    }
    mkToken(buffer, INTEIRO);
}

void Lexer::number() {
    if (isdigit(lookAhead())) {
        digit();
    } else {
        throw TokenInvalidError(current_position);
    }
}

void Lexer::factor() {
    if (isdigit(lookAhead())) {
        number();
    } else if (lookAhead() == '(') {
        paren_e(); expr(); paren_d();
    } else {
        throw TokenInvalidError(current_position);
    }
}
