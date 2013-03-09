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
            GeneralRegister,
            SpecialRegister,
            Subroutine
        };

        Value();
        Value(int);
        Value(const std::string &);
        Value(const char *);
        Value &setString(const char *);
        Value &setRegister(int);
        Value &setInteger(int);
        Value &setType(ValueType type) { m_type = type; return *this; }
        Value &setSubroutine(const char *);
       
        int integer();
        const char *string();
        int reg();
        const char *subroutine();
        char *toBytes();
        bool isRegister();
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
        Mnemonic(const string &name, vector<Value *> *args, Label *label)
        { }
        // TODO: Destructors

        bool hasLabel() { return (label != (Label *)0) ? true : false; }
        Label *label;
        string name;
        vector<Value *> *arguments;
    };

    class Buffer
    {
    public:
        size_t pushData(char *ptr, size_t size) {
            size_t s = getPointer();
            m_buffer.assign(ptr, ptr+size);
            return s;
        }
        Buffer &operator <<(char c) {
            m_buffer.push_back(c);
        }

        Buffer &operator <<(int i) {
            char *pi = (char *)&i;
            pushData(pi, sizeof(int));
        }
        size_t getPointer() { return m_buffer.size(); }
    private:
        vector<char> m_buffer;
    };


    class CodeBuffer
    {
    public:
        void addInstruction(opcode::Operation &, vector <Value *> &);
        size_t getCodePointer() { codeBuffer.size(); }

        CodeBuffer &operator <<(opcode::Operation &);
        CodeBuffer &operator <<(char);
        CodeBuffer &operator <<(int);
        CodeBuffer &operator <<(const std::string &);

    private:
        vector<char> codeBuffer;
    };

    struct Subroutine
    {
        Subroutine(Program *prog, vector<Label *> &labels, const string &name, size_t addr) 
            : program(program), labels(labels), name(name), codePointer(addr) { }

        Program *program;
        string name;
        vector<Label *> &labels;
        size_t codePointer;
        size_t subSize;
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