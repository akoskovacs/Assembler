#include <iostream>
#include <string>
#include <algorithm>

#include "opcodes.hxx"
#include "ast.hxx"

using namespace opcode;
using namespace ast;
using namespace std;

void encode(Mnemonic *mne)
{
    int op_ind;
    uint8_t opcode = 0;
    vector<char> *inst = new vector<char>;
    vector<Value *> *args = mne->arguments;

    try {
        op_ind = findOpcode(mne->name);
    } catch (...) {
        std::cerr << "Error: Instruction \'" << mne->name << "\' is unknown.\n";
        return; // TODO: Terminate
    }

    if (instruction_set[op_ind].op_args > mne->arguments->size()) {
        std::cerr << "Error: To many arguments for \'" << mne->name << "\' instruction.\n";
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

    inst->push_back(opcode);
    for (int i = 0; i < 2; i++) {
        switch (args[i]) {
            case Value::Integer:
                if (instruction_set[op_ind].op_arg_size == 2) {
                    
                } else {
                    inst->push_back((int8_t)(*it)->integer());
                }
            break;

            case Value::GeneralRegister:
                inst->push_back((int8_t) (*it)->generalRegister());
            break;

            case Value::SpecialRegister:
            
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
