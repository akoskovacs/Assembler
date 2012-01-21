/*
 * This is not a real Abstact Syntax Tree,
 * but for an assembler this may be enough.
*/

#ifndef AST_HXX
#define AST_HXX

#include <memory>
#include <vector>
#include <list>
#include <string>
#include <cstddef>
#include <cassert>

using namespace std;

namespace ast {
    struct Label;
    struct Mnemonic;
    const int REGISTER_COUNT = 13;

    enum ValueType {
        Nil,
        String,
        Integer,
        GeneralRegister,
        SpecialRegister,
        Subroutine
    };

    class Value
    {
    public:
        Value();
        Value(int);
        Value(const std::string &);
        Value(const char *);
        Value &setString(const char *);
        Value &setGeneralRegister(int);
        Value &setInteger(int);
        Value &setType(ValueType type) { m_type = type; return *this; }
        Value &setSubroutine(const char *);
       
        int integer();
        const char *string();
        int generalRegister();
        const char *subroutine();
        bool isRegister();
        ValueType type() { return m_type; }

    private:
        ValueType m_type;
        union {
            const char *v_string;
            uint16_t v_integer;
        } m_value;
    };

    struct Mnemonic 
    {
        Mnemonic(const string &name, vector<Value *> *args, Label *label) {
            this->name = name;
            arguments = args;
            this->label = label;
        }
        // TODO: Destructors

        bool hasLabel() { return (label != (Label *)0) ? true : false; }
        Label *label;
        string name;
        vector<Value *> *arguments;
    };

    struct Subroutine
    {
        Subroutine(const string &name, vector<Mnemonic *> *mnemonics) {
            this->name = name;
            this->mnemonics = mnemonics;
        }

        string name;
        vector<Mnemonic *> *mnemonics;
    };

    struct Label
    {
        Label(const string &name)
            : name(name)
        {
//            if (prog != 0)
//                parent->labels->push_back(prog);
        }

        string name; 
    };

    struct Program
    {
       Program(vector<Subroutine *> *subs = 0)
       { subroutines = subs; }

       vector<Label *> *labels;
       vector<Subroutine *> *subroutines;
    };
} // namespace parser

#endif // AST_HXX
