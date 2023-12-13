#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <stdexcept>

enum TokenType {
    INTEIRO,
    OP_MAIS,
    OP_MENOS,
    OP_MULT,
    OP_DIV,
    T_PAR_ESQ,
    T_PAR_DIR,
    T_ESPACO,
    FIM
};

std::string tokenTypeToString(TokenType type);

struct Token {
    TokenType tipo;
    std::string valor;
};

class TokenInvalidError : public std::runtime_error {
public:
    TokenInvalidError(const std::string& message, int index);
    TokenInvalidError(int index);
    int getIndex();

private:
    int index;
};

#endif
