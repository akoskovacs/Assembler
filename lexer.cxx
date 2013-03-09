#include <cctype>
#include "lexer.hxx"

using namespace lexer;

char Lexer::copyToText()
{
    char ch;
    m_text = "";
    while ((m_stream >> ch) && (std::isalpha(ch) || ch == '_'))
          m_text += ch;
    return ch;
}

lexer::Token lexer::Lexer::lex()
{
    char ch;
    while (m_stream >> ch) {
        if (std::isspace(ch))
            continue;

        switch (ch) {
            // Eat comments
            case ';':
                while ((m_stream >> ch) && ch != '\n')
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
               while ((m_stream >> ch) && ch != '"') 
                   m_text += ch;
            return tString;

            // Register
            case '%':
                if ((m_stream >> ch) && ch == 'r') {
                    m_stream >> m_integer;
                    return tGeneralReg;
                } else {
                    while ((m_stream >> ch)
                    return tSpecialReg;
                }
            break;
        }

        if (std::isalpha(ch) || ch == '_') {
            m_stream.putback(ch);
            char nc = copyToText();
            if (nc == ':')
                return tSubName;
            else
                return tMnemonic;
        }

        if (std::isdigit(ch) || ch == '-' || ch == '+') {
            if (ch == '0') {
                m_stream >> ch;
                if (ch == 'x' || ch == 'X') {
                    // Hexadecimal (starting with 0x or 0X)
                    m_stream >> std::hex >> m_integer;
                    return tInteger;
                } else if (std::isdigit(ch)) {
                    // Octal (starting with zero and than other digits)
                    m_stream.putback(ch);
                    m_stream >> std::oct >> m_integer;
                    return tInteger;
                } else {
                    // Just a zero
                    m_integer = 0;
                    return tInteger;

                }
            }
            // Decimal
            m_stream.putback(ch);
            m_stream >> m_integer;
            return tInteger;
        }
    }
    return tEof;
}
