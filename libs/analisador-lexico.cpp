#include <iostream>
#include <vector>
#include <cctype>
#include <queue>
#include "token.hpp"
#include "analisador-lexico.hpp"

Lexer::Lexer(const std::string& src) : source_code(src) , tokenIndex(0), tokens() {

    std::size_t current_position = 0;
    std::queue<char> buffer;

    for(const char currentChar : source_code){
        
        if (isdigit(currentChar)) {
            buffer.push(currentChar);
        }else{

            if (!buffer.empty()) {
                mkToken(bufferToString(buffer), INTEIRO);
                while (!buffer.empty()) {
                    buffer.pop();
                }
            }

            TokenType tokenType;
            switch (currentChar) {
                case '+':
                    tokenType = OP_MAIS;
                    break;
                case '-':
                    tokenType = OP_MENOS;
                    break;
                case '*':
                    tokenType = OP_MULT;
                    break;
                case '/':
                    tokenType = OP_DIV;
                    break;
                case '(':
                    tokenType = T_PAR_ESQ;
                    break;
                case ')':
                    tokenType = T_PAR_DIR;
                    break;
                default:
                    throw TokenInvalidError(current_position);
                    break;
            }

            mkToken(std::string(&currentChar, 1), tokenType);
        }
        current_position++;
    }

    if (!buffer.empty()) {
        mkToken(bufferToString(buffer), INTEIRO);
    }
}

std::string Lexer::bufferToString(std::queue<char>& buffer){
    return std::string(&buffer.front(), buffer.size());
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

std::vector<Token>* Lexer::getTokens(){
    return &tokens;
}