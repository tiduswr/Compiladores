#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include "analisador-lexico.hpp"
#include "analisador-sintatico.hpp"
#include "token.hpp"

Parser::Parser(const std::string& source_code) : lexer(Lexer(source_code)) , current_position(0){
    expr();
}

Token Parser::lookAhead(){
    std::vector<Token>* v = lexer.getTokens();

    return (current_position < v->size()) ? v->at(current_position) : NULL_TOKEN;
}

void Parser::match(const std::string& token){
    if((current_position < lexer.getTokens()->size()) && compareTokenValue(lookAhead(), token)){
        current_position++;
    }else{
        std::cout << "Erro funcao match()\n";
        throw TokenInvalidError(current_position);
    }
}

void Parser::paren_e(){
    if(compareTokenValue(lookAhead(), "(")){
        match("(");
    }else{
        std::cout << "Erro funcao paren_e()\n";
        throw TokenInvalidError(current_position);
    }
}

void Parser::paren_d(){
    if(compareTokenValue(lookAhead(), ")")){
        match(")");
    }else{
        std::cout << "Erro funcao paren_d()\n";
        throw TokenInvalidError(current_position);
    }
}

void Parser::op(){
    const std::vector<std::string> operators = {"+", "-", "*", "/"};

    for(const auto& op : operators){
        if(compareTokenValue(lookAhead(), op)){
            match(op);
            break;
        }
    }
}

void Parser::expr(){
    term(); expr_tail();
}

void Parser::expr_tail(){
    if(compareTokenValue(lookAhead(), "+") || compareTokenValue(lookAhead(), "-")){
        op(); term(); expr_tail();
    }
}

void Parser::term(){
    factor(); term_tail();
}

void Parser::term_tail(){
    if(compareTokenValue(lookAhead(), "*") || compareTokenValue(lookAhead(), "/")){
        op(); factor(); term_tail();
    }
}

void Parser::factor() {
    if (isInteger(lookAhead().valor)) {
        number();
    } else if (compareTokenValue(lookAhead(), "(")) {
        paren_e(); expr(); paren_d();
    } else {
        std::cout << "Erro funcao factor()\n";
        //std::cout << "lookAhead().valor = " + lookAhead().valor + "; lookAhead().tipo = " + tokenTypeToString(lookAhead().tipo);
        throw TokenInvalidError(current_position);
    }
}

void Parser::number() {
    if (!lookAhead().valor.empty() && isInteger(lookAhead().valor)) {
        match(lookAhead().valor);
    } else {
        std::cout << "Erro funcao number()\n";
        throw TokenInvalidError(current_position);
    }
}

bool Parser::isInteger(const std::string& s) {
    for (const auto& c : s) {
        if (!isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}