#include <iostream>
#include <string>
#include <algorithm>

#include "opcodes.hxx"
#include "ast.hxx"
#include "linker.hxx"

using namespace opcode;
using namespace ast;
using namespace std;

void Mnemonic::genCode(Linker &linker)
{
    int op_ind;
    uint8_t opcode = 0;
    vector<Value *> *args = mne->arguments;
    CodeBuffer &code = linker.code();

    try {
        op_ind = findOpcode(mne->name);
    } catch (...) {
        std::cerr << "Error: Instruction \'"
                  << mne->name << "\' is unknown.\n";
        return; // TODO: Terminate
    }

    if (instruction_set[op_ind].op_args > mne->arguments->size()) {
        std::cerr << "Error: To many arguments for \'"
                  << mne->name << "\' instruction.\n";
        return; // TODO: Terminate
    }

    opcode = instruction_set[op_ind].op_code;
    if (args->at(0)->isRegister())
        opcode |= 0x20;

    if (args->at(1)->isRegister())
        opcode |= 0x40;
    else if (args->at(1)->isIntermediate())
        opcode |= 0x80;
    else
        opcode |= 0xC0;

    code << opcode;
    for (int i = 0; i < 2; i++) {
        switch (args[i]) {
            case Value::Integer:
                if (instruction_set[op_ind].op_args > 1) {
                    code << args[i]->integer();
                }
            break;

            case Value::Register:
                code << (uint8_t)args[i]->integer();
            break;

            case Value::String:
            break;

            case Value::Subroutine:
            break;
            
            default:
            break;
        }
    }

    return;
}
// TODO: Replace with binary search
const Operation *Instruction::findOpcode(const string &name)
{
    Operation *op = instruction_set;
    for (register int i = 0; i < INSTRUCTION_SET_SIZE; i++, op++) {
        if (name == instruction_set[i].op_name)
            return instruction_set[i];
    }
    throw i; // TODO: Normal exceptions
}

#if 0
int Instruction::findOpcode(const string &name)
{
    Operation *op = instruction_set[0];
    int index;
    if (!std::binary_search(op, op + INSTRUCTION_SET_SIZE, index, inst_cmp))
        throw i; // TODO: Normal exceptions
    return index;
}
#endif
