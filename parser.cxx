#include "ast.hxx"
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
    std::vector<Label *> *labels = new std::vector<Label *>;
    std::vector<Mnemonic *> *mnes = new std::vector<Mnemonic *>;
    std::string sub_name;
    Subroutine *s = new Subroutine(this, sub_name, labels, mnes);
    if (m_current_token == tSubName) {
        sub_name = m_lexer->text();
        while (nextToken() != tSubName) {
            switch (m_current_token) {
                case tLabel:
                    labels->push_back(
                        new Label(s, m_lexer->text(), mnes->size()));
                break;

                case tMnemonic:
                    mnes->push_back(parseMnemonic());
                break;
            }
        }
    }
    return s;
}

ast::Mnemonic *Parser::parseMnemonic()
{
    std::vector<Value *> *args = new std::vector<Value *>;
    std::string mne_name;
    Mnemonic *mne;
    Value *v;

    if (m_current_token == tMnemonic) {
        mne_name = m_lexer->text();
        mne = new Mnemonic(mne_name, args);
        while (nextToken() != '\n') {
            switch (m_current_token) {
                case lexer::tInteger:
                    v = new Value(m_lexer->integer());        
                    args->push_back(v);
                break;

                case lexer::tSpecialReg:
                    v = new Value;
                    v->setRegister(m_lexer->text());
                    args->push_back(v);
                break;

                case lexer::tGeneralReg:
                    v = new Value;
                    v->setRegister(m_lexer->integer());
                    args->push_back(v);
                break;

                case lexer::tString:
                    v = new Value(m_lexer->text());
                break;

                case lexer::tColon:
                continue;
            }
        }
    }
    return mne;
}
