#include "parser.hxx"
#include "opcodes.hxx"
#include <string>
#include <map>

using namespace ast;
using namespace lexer;

Program *Parser::parse()
{
    if (m_lexer == 0)
        return;

    while (nextToken() == tSubName) {
        Subroutine *sub = parseSubroutine();
        if (sub != 0)
            subroutines.push_back(sub);
    }
    return m_program;
}

Subroutine *Parser::parseSubroutine()
{
    std::vector<char> instructions;
    std::vector<Label *> labels;
    std::string sub_name;
    Label *l;
    Subroutine *s =
        new Subroutine(this, labels, sub_name, code.getCodePointer());
    if (m_current_token == tSubName) {
        sub_name = m_lexer.text();
        while (nextToken() != tSubName) {
            switch (m_current_token) {
                case tLabel:
                l = new Label(s, m_lexer->text(), code.getCodePointer());
                labels.push_back(l);
                continue;

                case tMnemonic:
                instructions = parseMnemonic(s);
                break;
            }
        }
    }
    return s;
}

void Parser::parseMnemonic(Subroutine *s)
{
    if (m_current_token == tMnemonic) {
        Operation op = opcode::findOpcode(m_lexer->text());
        while (nextToken() != '\n') {
            switch (m_current_token) {
                case lexer::tInteger:
                    
                break;

                case lexer::tGeneralReg:

                break;

            }
        }
    }
}
