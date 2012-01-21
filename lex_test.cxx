#include <stdio.h>
#include <fstream>
#include "lexer.hxx"
//#include <sstream>

int main(int argc, const char *argv[])
{
    std::fstream test("test.S");
//  std::istringstream str("main:\nmov %r0, %r1\nret\n");
    lexer::Token curr_tok;
    lexer::Lexer lexer(&test);
    while ((curr_tok = lexer.lex())) {
        switch (curr_tok)
        {
            case lexer::tSubName:
                    printf("Got subroutine %s\n", lexer.text().c_str());
                break;

                case lexer::tGeneralReg:
                    printf("Got general register %%r%d\n", lexer.integer());
                break;

                case lexer::tInteger:
                    printf("Got integer %d\n", lexer.integer());
                break;

                case lexer::tMnemonic:
                    printf("Got mnemonic %s\n", lexer.text().c_str());
                break;

                case lexer::tLabel:
                    printf("Got jump label %s\n", lexer.text().c_str());
                break;

                case lexer::tString:
                    printf("Got string %s\n", lexer.text().c_str());
                break;
        }
    }
    return 0;
}
