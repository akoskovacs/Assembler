#ifndef LEXER_HXX
#define LEXER_HXX

#include <iostream>

namespace lexer {
    enum Token {
        tEof = 0,
        tInteger,
        tString,
        tJumpTarget,
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
        explicit Lexer(std::istream *stream = &std::cin) 
            : m_stream(stream) {}
   
        Token lex();

        const std::string &text() { return m_text; }
        int integer() { return m_integer; }

        void setStream(std::istream *stream)
        { m_stream = stream; }
        std::istream *stream() { return m_stream; }

    private:
        char copyToText();
        inline char nextChar() {
            char ch;
            m_stream->get(ch);
            return ch;
        }

        std::istream *m_stream;
        Token m_currentToken;
        int m_integer;
        std::string m_text;
    }; // class Lexer
} // namespace lexer

#endif // LEXER_HXX
