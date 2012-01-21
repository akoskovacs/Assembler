#include <iostream>
#include <string>
#include <algorithm>

#include "opcodes.hxx"
#include "ast.hxx"

using namespace opcode;
using namespace ast;
using namespace std;
namespace {
    union Converter {
        int16_t ui16;
        int8_t ui8[2];
    };
}

vector<char> *Instruction::encode(Mnemonic *mne)
{
    int op_ind;
    unsigned char opcode = 0;
    vector<char> *inst = new vector<char>;
    vector<Value *> *args = mne->arguments;

    try {
        op_ind = findOpcode(mne->name);
    } catch (...) {
        std::cerr << "Error: Instruction \'" << mne->name << "\' is unknown.\n";
        return inst; // TODO: Terminate
    }

    if (instruction_set[op_ind].op_args > mne->arguments->size()) {
        std::cerr << "Error: To many arguments for \'" << mne->name << "\' instruction.\n";
        return inst; // TODO: Terminate
    }

    opcode = instruction_set[op_ind].op_code;
    if (args->at(1)->isRegister())
        opcode |= 0x40;

    if (args->at(1)->isRegister())
        opcode |= 0x80;

    inst->push_back(opcode);
    vector<Value *>::const_iterator it;
    Converter long_arg;
    for (it = args->begin(); it != args->end(); it++) {
        switch ((*it)->type()) {
            case Integer:
                if (instruction_set[op_ind].op_arg_size == 2) {
                    long_arg.ui16 = (int16_t)(*it)->integer();
                    inst->push_back((int8_t)long_arg.ui8[1]);
                    inst->push_back((int8_t)long_arg.ui8[0]);
                } else {
                    inst->push_back((int8_t)(*it)->integer());
                }
            break;

            case GeneralRegister:
                inst->push_back((int8_t) (*it)->generalRegister());
            break;

            default:
            break;
        }
    }

    return inst;
}
// TODO: Replace with binary search
int Instruction::findOpcode(const string &name)
{
    Operation *op = instruction_set[0];
    for (register int i = 0; i < INSTRUCTION_SET_SIZE; i++, op++) {
        if (name == instruction_set[i].op_name)
            return i;
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
