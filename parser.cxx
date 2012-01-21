#include "parser.hxx"

using namespace ast;
using namespace lexer;

Program *Parser::parse()
{
    vector<parser::Subroutine *> *subs;
    if (m_lexer == 0)
        return;

    while (nextToken() == tSubName) {
        Subroutine *sub = parseSubroutine();
        if (sub != 0)
            subs->push_back(sub);
    }
    m_program->subroutines = subs;
    return m_program;
}

Subroutine *Parser::parseSubroutine()
{
    std::vector<Mnemonic *> *instructions = new std::vector<Mnemonic *>;
    std::string sub_name;
    Label *label = 0;
    if (m_current_token == tSubName) {
        sub_name = m_lexer.text();
        while (nextToken() != tSubName) {
            switch (m_current_token) {
                case tLabel:
                    label = new Label(m_lexer.text());
                continue;

                case tMnemonic:
                    Mnemonic *tmp = parseMnemonic();
                    if (label != 0) {
                        tmp->setLabel(label);
                        m_program->labels->push_back(label);
                        label = 0;
                    }

                    instructions->push_back(tmp);
                break;
            }
        }
    } else {
        return (Subroutine *)0;
    }
}

Mnemonic *Parser::parseMnemonic()
{
    std::string mne_name;
    std::vector<Value *> *args = new std::vector<Value *>;
    if (m_current_token == tMnemonic) {
        mne_name = m_lexer->text();
        Token tok;
        while ((tok = nextToken()) && tok != '\n')
        switch (tok) {
            case tMnemonic: 
                Value *val = Value();
                if (mne_name == "call") {
                    val->setSubroutine(m_lexer->text());
                // Is it a jump instruction?
                } else if (mne_name[0] == 'j') {
                    val->setLabel(m_lexer->text());
                } else {
                    continue; // TODO: Handle nop and ret
                }

                args->push_back(val);
                return new Mnemonic(mne_name, args);
            break;

            case tInteger:
                args->push_back(new Value(m_lexer->integer()));
            break; 

            case tString:
                args->push_back(new Value(m_lexer->text()));
            break; 

            case tColon:
            continue;

            case tGeneralReg:
                Value *val = Value();
                val->setGeneralRegister(m_lexer->integer());
                args->push_back(val);
            break; 

            case tLabel:
            continue; // TODO: Resolve the label
        }

        return new Mnemonic(mne_name, args);
    } else {
        return (Mnemonic *)0;
    }
}
