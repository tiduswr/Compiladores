#include <stdexcept>
#include "token.hpp"

const Token NULL_TOKEN = {FIM, ""};

std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case INTEIRO: return "INTEIRO";
        case OP_MAIS: return "OP_MAIS";
        case OP_MENOS: return "OP_MENOS";
        case OP_MULT: return "OP_MULT";
        case OP_DIV: return "OP_DIV";
        case T_PAR_ESQ: return "T_PAR_ESQ";
        case T_PAR_DIR: return "T_PAR_DIR";
        case T_ESPACO: return "T_ESPACO";
        case FIM: return "FIM";
        default: return "DESCONHECIDO";
    }
}

bool compareTokens(const Token& tk1, const Token& tk2){
    return (tk1.valor == tk2.valor) && (tk1.tipo == tk2.tipo);
}

bool compareTokenValue(const Token& tk1, const std::string& value){
    return tk1.valor == value;
}

TokenInvalidError::TokenInvalidError(const std::string& message, int index) : 
    std::runtime_error(message + "(index=" + std::to_string(index) + ")") {
        this->index = index;
}

TokenInvalidError::TokenInvalidError(int index) : 
    std::runtime_error("Token Invalido(index=" + std::to_string(index) + ")") {
        this->index = index;
}

int TokenInvalidError::getIndex(){
    return this->index;
}