#include <iostream>
#include "libs/analisador-lexico.hpp"

int main(int argc, char const *argv[]) {
    std::string source_code(argv[1]);

    Lexer lex = Lexer(source_code);

    Token t = lex.getNextToken();
    while(t.tipo != FIM){
        std::cout << "Tipo: " + tokenTypeToString(t.tipo) + ", Valor: " + t.valor << std::endl;
        t = lex.getNextToken();
    }

    return 0;
}
