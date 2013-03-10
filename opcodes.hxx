#ifndef OPCODES_HXX
#define OPCODES_HXX

#include <vector>
#include <cstddef>
#include <sstream>
#include <vector>

#include "ast.hxx"

namespace opcode {
   /* 
    * FA_*          ~      First argument type
    * SA_*          ~      Second argument type
    * ?A_Address    ~      A memory address
    * ?A_Reg        ~      A register id
    * ?A_IMed       ~      A value, embedded in the instruction
    * ?A_Any        ~      Can be an address, register or an intermediate value
    * ?A_Mem        ~      Can hold only register or address
    */
   enum InstructionType {
        NoArg = 0x0
        , FA_Address = 0x001, FA_Reg = 0x002, FA_IMed = 0x004
        , FA_Mem = FA_Address|FA_Reg
        , FA_Any = FA_Mem|FA_IMed

        , SA_Address = 0x008, SA_Reg = 0x010, SA_IMed = 0x020
        , SA_Mem = SA_Address|SA_Reg
        , SA_Any = SA_Mem|SA_IMed
   };

   const char *special_registers[] = {
        "ip", "sp"
   };

   struct Operation {
        const char *op_name;      /* Mnemonic of the operation's code */
        const char op_code;       /* Operation code -- without the type flags -- */

        const size_t op_args;     /* Argument count */
        int op_type;              /* Types of the arguments */
        const size_t op0_arg_size; /* Size of the first argument */
        const size_t op1_arg_size; /* Size of the second argument */
    /* -- Full instruction set -- [XXX: binary searched, keep in this order!] */
    /* ## NOTICE: These instructions are not really complete, some mnemonics ##
                ##  and opcodes may change in the near future! ## */
        int argCount() const {}
   };
   
   enum Opcode {
        ADD = 0x1, AND , BR , CALL , CMP , DEC , DIV , INC
        , MUL , MOD , MOV , NOP , OR , POP , PUSH , RET
        , SL , SR , SUB , XOR
   };

   enum SpecialRegisters {
        SP, IP
   };

   static const Operation instruction_set[] = {
        { "add",    Opcode::ADD,  FA_Mem|SA_Any, 2, 4, 4 },
        { "and",    Opcode::AND,  FA_Mem|SA_Any, 2, 2, 5 },
        { "br",     Opcode::BR,   FA_Mem|SA_Mem, 4, 4, 2 },
        { "call",   Opcode::CALL, FA_Mem,        1, 1, 3 },
        { "cmp",    Opcode::CMP,  FA_Mem|SA_Any, 2, 2, 5 },
        { "dec",    Opcode::DEC,  FA_Mem,        1, 2, 2 },
        { "div",    Opcode::DIV,  FA_Mem|SA_Any, 2, 2, 5 },
        { "inc",    Opcode::INC,  FA_Mem,        1, 2 },
        { "mul",    Opcode::MUL,  FA_Mem|SA_Any, 2, 5 },
        { "mov",    Opcode::MOV,  FA_Any|SA_Mem, 1, 3 },
        { "nop",    Opcode::NOP,  NoArg,         0, 0, 1 },
        { "or",     Opcode::OR,   FA_Mem|SA_Any, 2, 2, 5 },
        { "pop",    Opcode::POP,  FA_Mem,        2, 3 },
        { "push",   Opcode::PUSH, FA_Any,        1, 2, 3 },
        { "ret",    Opcode::RET,  NoArg,         0, 0, 1 },
        { "sl",     Opcode::SL,   FA_Mem,        1, 1, 3 },
        { "sr",     Opcode::SR,   FA_Mem,        1, 3 },
        { "sub",    Opcode::SUB,  FA_Mem|SA_Any, 2, 5 },
        { "xor",    Opcode::XOR,  FA_Mem|SA_Any, 2, 3 }
    };
    const int INSTRUCTION_SET_SIZE = sizeof(instruction_set)/sizeof(instruction_set[0]);

static int findOpcode(const std::string &);

} // namespace opcode

#endif // OPCODES_HXX
