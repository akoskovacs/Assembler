#include <cctype>
#include "lexer.hxx"

using namespace lexer;

char Lexer::copyToText()
{
    char ch;
    m_text = "";
    while ((ch = nextChar()) && (isalpha(ch) || ch == '_'))
          m_text += ch;
    return ch;      
}

Token Lexer::lex()
{
    char ch;
    while ((ch = nextChar())) {
        if (m_stream->eof())
            return tEof;

        if (std::isspace(ch))
            continue;

        switch (ch) {
            char nc;
            // Eat comments
            case ';':
                while (nextChar() != '\n')
                    ;

            case '\n':
                m_currentLine++;
            return tNewLine;

            case ',':
            return tColon;

            // Jump target
            case '.':
               copyToText();
            return tLabel;

            case '"':
               m_text = "";
               while ((nc = nextChar()) && nc != '"') 
                   m_text += nc;
            return tString;

            // Register
            case '%':
                if ((nc = nextChar()) && nc == 'r') {
                    m_stream->operator>>(m_integer);
                    return tGeneralReg;
                } else {
                    copyToText();
                    return tSpecialReg;
                }
        }

        if (std::isalpha(ch) || ch == '_') {
            m_stream->putback(ch);
            char nc = copyToText();
            if (nc == ':')
                return tSubName;
            else
                return tMnemonic;
        }

        if (std::isdigit(ch) || ch == '-' || ch == '+') {
            if (ch == '0') {
                char nc = nextChar();
                if (nc == 'x' || nc == 'X') {
                    // Hexadecimal (starting with 0x or 0X)
                    m_stream->operator>>(std::hex) >> m_integer;
                    return tInteger;
                } else if (std::isdigit(nc)) {
                    // Octal (starting with zero and than other digits)
                    m_stream->putback(nc);
                    m_stream->operator>>(std::oct) >> m_integer;
                    return tInteger;
                } else {
                    // Just a zero
                    m_integer = 0;
                    return tInteger;

                }
            }
            // Decimal
            m_stream->putback(ch);
            m_stream->operator>>(m_integer);
            return tInteger;
        }
    }
    return tEof;
}
