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
        const size_t op_arg_size; /* Size of the arguments */
        const size_t op_size;     /* Maximum size of the instruction, */
    };                            /* in bytes (including the opcode itself) */
    /* -- Full instruction set -- [XXX: binary searched, keep in this order!] */
    /* ## NOTICE: These instructions are not really complete, some mnemonics ##
                ##  and opcodes may change in the near future! ## */
    static const Operation instruction_set[] = {
        { "add",    0x0,  2, 2, 5 },
        { "addb",   0x1,  2, 1, 3 },
        { "and",    0x2,  2, 2, 5 },
        { "andb",   0x3,  2, 1, 3 },
        { "call",   0x4,  1, 1, 3 },
        { "cmp",    0x5,  2, 2, 5 },
        { "cmpb",   0x6,  2, 1, 3 },
        { "dec",    0x7,  1, 2, 2 },
        { "div",    0x8,  2, 2, 5 },
        { "divb",   0x9,  2, 1, 3 },
        { "inc",    0xA,  1, 1, 2 },
        { "je",     0xB,  1, 2, 3 },
        { "jg",     0xC,  1, 2, 3 },
        { "jl",     0xD,  1, 2, 3 },
        { "jmp",    0xE,  1, 2, 3 },
        { "jne",    0xF,  1, 2, 3 },
        { "mul",    0x10, 2, 2, 5 },
        { "mulb",   0x11, 2, 1, 3 },
        { "nop",    0x12, 0, 0, 1 },
        { "or",     0x13, 2, 2, 5 },
        { "orb",    0x14, 2, 1, 3 },
        { "pop",    0x15, 1, 2, 3 },
        { "popb",   0x16, 1, 1, 2 },
        { "push",   0x17, 1, 2, 3 },
        { "pushb",  0x18, 1, 1, 2 },
        { "ret",    0x19, 0, 0, 1 },
        { "sl",     0x1A, 1, 1, 3 },
        { "sr",     0x1B, 1, 1, 3 },
        { "sub",    0x1C, 2, 2, 5 },
        { "subb",   0x1D, 2, 1, 3 },
        { "xor",    0x1E, 2, 2, 3 },
        { "xorb",   0x1F, 2, 1, 3 }
    };
    const int INSTRUCTION_SET_SIZE = sizeof(instruction_set)/sizeof(instruction_set[0]);

class Instruction {
public:
   static std::vector<char> encode(ast::Mnemonic *);
   static int findOpcode(const std::string &);

   private:

}; // class Instruction

} // namespace opcode

#endif // OPCODES_HXX
