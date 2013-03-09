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
        char *toBytes();
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
        Mnemonic(const string &name, vector<Value *> *args, Label *label)
        { }
        // TODO: Destructors

        bool hasLabel() { return (label != (Label *)0) ? true : false; }
        Label *label;
        string name;
        vector<Value *> *arguments;
    };

    class Code
    {
    public:
        Code();
        void addInstruction(opcode::Operation &, vector <Value *> &);
        size_t getCodePointer() { codeBuffer.size(); }
    private:
        vector<char> codeBuffer;
    }

    struct Subroutine
    {
        Subroutine(Program *prog, vector<Label *> &labels, const string &name, size_t addr) 
            : program(program), labels(labels), name(name), codePointer(addr) { }

        Program *program;
        string name;
        vector<Label *> &labels;
        size_t codePointer
    };

    struct Label
    {
        Label(Subroutine *sub, const string &name, size_t addr)
            : subroutine(sub), name(name), codePointer(addr) { }

        Subroutine *subroutine;
        string name; 
        size_t codePointer;
    };

    struct Program
    {
       Program() { }

       Code code;
       vector<Subroutine *> subroutines;
       vector<char *> strings;
    };
} // namespace parser

#endif // AST_HXX
