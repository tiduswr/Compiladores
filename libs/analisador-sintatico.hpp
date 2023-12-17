#include <iostream>
#include <string>
#include "analisador-lexico.hpp"

class Parser{
    public:
        Parser(const std::string& source_code);
        Lexer lexer;
        
    private:
        std::size_t current_position;

        Token lookAhead();
        void match(const std::string& token);
        bool isInteger(const std::string& s);  
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