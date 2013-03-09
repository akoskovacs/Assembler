#ifndef OPCODES_HXX
#define OPCODES_HXX

#include <vector>
#include <cstddef>
#include <sstream>
#include <vector>

#include "ast.hxx"

namespace opcode {
   struct Operation {
        const char *op_name;      /* Mnemonic of the operation's code */
        const char op_code;       /* Operation code -- without the type flags -- */
        const size_t op_args;     /* Argument count */
        const size_t op0_arg_size; /* Size of the first argument */
        const size_t op1_arg_size; /* Size of the second argument */
    /* -- Full instruction set -- [XXX: binary searched, keep in this order!] */
    /* ## NOTICE: These instructions are not really complete, some mnemonics ##
                ##  and opcodes may change in the near future! ## */
    enum Opcode {
          ADD , AND , BR , CALL , CMP , DEC , DIV , INC
        , MUL , MOD , MOV , NOP , OR , POP , PUSH , RET
        , SL , SR , SUB , XOR
    };

    static const Operation instruction_set[] = {
        { "add",    Opcode::ADD,  2, 4, 4 },
        { "and",    Opcode::AND,  2, 2, 5 },
        { "br",     Opcode::BR,   4, 4, 2 },
        { "call",   Opcode::CALL, 1, 1, 3 },
        { "cmp",    Opcode::CMP,  2, 2, 5 },
        { "cmp",    Opcode::DIV,  2, 2, 5 },
        { "dec",    Opcode::DEC,  1, 2, 2 },
        { "div",    Opcode::DIV,  2, 2, 5 },
        { "inc",    Opcode::INC,  1, 1, 2 },
        { "mul",    Opcode::MUL,  2, 2, 5 },
        { "mov",    Opcode::MOV,  2, 1, 3 },
        { "nop",    Opcode::NOP,  0, 0, 1 },
        { "or",     Opcode::OR,   2, 2, 5 },
        { "pop",    Opcode::POP,  1, 2, 3 },
        { "push",   Opcode::PUSH, 1, 2, 3 },
        { "ret",    Opcode::RET,  0, 0, 1 },
        { "sl",     Opcode::SL,   1, 1, 3 },
        { "sr",     Opcode::SR,   1, 1, 3 },
        { "sub",    Opcode::SUB,  2, 2, 5 },
        { "xor",    Opcode::XOR,  2, 2, 3 },
    };
    const int INSTRUCTION_SET_SIZE = sizeof(instruction_set)/sizeof(instruction_set[0]);

static int findOpcode(const std::string &);

} // namespace opcode

#endif // OPCODES_HXX
