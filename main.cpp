#include <iostream>
#include "libs/analisador-sintatico.hpp"
#include "libs/token.hpp"

int main(int argc, char const *argv[]) {
    
    std::string input;

    if(argc <=1 || (argc > 1 && (argv[1][0] == '\0'))){
        //Valor teste
        input = "(3+22)*12";
    }else{
        input = argv[1];
    }

    Parser parser = Parser(input);

    Token t = parser.lexer.getNextToken();
    while(t.tipo != FIM){
        std::cout << "Tipo: " + tokenTypeToString(t.tipo) + ", Valor: " + t.valor << std::endl;
        t = parser.lexer.getNextToken();
    }

    return 0;
}
