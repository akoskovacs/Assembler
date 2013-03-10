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

#include "opcodes.hxx"

#if _MSC_VER
    typedef unsigned char uint8_t;
    typedef signed char int8_t;
    typedef unsigned __int16 uint16_t;
    typedef unsigned __int16 int16_t;
    typedef unsigned __int32 uint32_t;
    typedef unsigned __int32 int32_t;
#endif

namespace ast {
    struct Label;
    struct Mnemonic;

    class Value
    {
    public:
         enum ValueType {
            Nil,
            String,
            Integer,
            Register,
            Subroutine
        };

        Value();
        Value(int);
        Value(const std::string &);
        Value(const char *);
        Value &setString(const char *);
        Value &setRegister(int);
        Value &setRegister(const std::string &);
        Value &setInteger(int);
        Value &setType(ValueType type) { m_type = type; return *this; }
        Value &setSubroutine(const char *);
       
        int integer();
        const char *string();
        int reg();
        const char *subroutine();
        char *toBytes();
        bool isRegister();
        bool isIntermediate() { return !isRegister(); }
        ValueType type() { return m_type; }

    private:
        ValueType m_type;
        union {
            const char *v_string;
            int         v_integer;
        } m_value;
    };

    struct Mnemonic 
    {
        Mnemonic(const string &name, vector<Value *> *args, Label *label = 0)
            : name(name), arguments(args), label(label)
        { }

        void genCode(CodeBuffer &code, DataBuffer &data);
        Label *label;
        std::string name;
        std::vector<Value *> &arguments;
    };

    struct Subroutine
    {
        Subroutine(Program *prog, const string *name
            , std::vector<Mnemonic *> *mne, std::vector<Label *> *labels) 
            : program(program), name(name), mnemonics(mne), labels(labels) { }

        Program *program;
        std::string *name;
        std::vector<Mnemonic *> *mnemonics;
        std::vector<Label *> *labels;
    };

    struct Label
    {
        Label(Subroutine *sub, const string &name, size_t addr)
            : subroutine(sub), name(name), codePointer(addr) { }

        Subroutine *subroutine;
        std::string name; 
        size_t codePointer;
    };

    struct Program
    {
       void genCode(CodeBuffer &code, DataBuffer &data) {
           std::vector<Subroutine *>::iterator it;
           for (it = subroutines.begin(); it != subroutines.end(); it++) {
               it->genCode(code, data);
           }
       }
       std::vector<Subroutine *> subroutines;
    };
} // namespace parser

#endif // AST_HXX
