#ifndef PARSER_HXX
#define PARSER_HXX

#include <iostream>

#include "lexer.hxx"
#include "ast.hxx"

using namespace std;
using namespace ast;

namespace parser {
    class Parser
    {
    public:
        explicit Parser(lexer::Lexer *lex = 0) 
            : m_lexer(lex) { m_program = new Program; }

        ast::Program *parse();
    
    private:
        Mnemonic *parseMnemonic();
        Subroutine *parseSubroutine();

        lexer::Token nextToken() {
            return m_current_token = m_lexer->lex();
        }

        lexer::Token m_current_token;
        auto_ptr<lexer::Lexer> m_lexer;
        ast::Program *m_program;
    }; // class Parser
} // namespace parser

#endif // PARSER_HXX
