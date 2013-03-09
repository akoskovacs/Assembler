#ifndef LEXER_HXX
#define LEXER_HXX

#include <iostream>

namespace lexer {
    enum Token {
        tEof = 0,
        tInteger,
        tString,
        tLabel,
        tSubName,
        tGeneralReg,
        tSpecialReg,
        tMnemonic,
        tColon = ',',
        tNewLine = '\n'
    };

    class Lexer 
    {
    public:
        explicit Lexer(std::istream &stream = std::cin) 
            : m_stream(stream), m_currentLine(1) {}
   
        Token lex() const;

        std::string &text() { return m_text; }
        int integer() const { return m_integer; }
        int currentLine() const { return m_currentLine; }

        std::istream &stream() { return m_stream; }

    private:
        char copyToText();

        std::istream &m_stream;
        int m_currentLine;
        Token m_currentToken;
        int m_integer;
        std::string m_text;
    }; // class Lexer
} // namespace lexer

#endif // LEXER_HXX
