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
    FIM,
    VAZIO
};

struct Token {
    TokenType tipo;
    std::string valor;
};

extern const Token NULL_TOKEN;

std::string tokenTypeToString(TokenType type);

bool compareTokens(const Token& tk1, const Token& tk2);

bool compareTokenValue(const Token& tk1, const std::string& value);

class TokenInvalidError : public std::runtime_error {
public:
    TokenInvalidError(const std::string& message, int index);
    TokenInvalidError(int index);
    int getIndex();

private:
    int index;
};

#endif
