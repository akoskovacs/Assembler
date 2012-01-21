#ifndef LINKER_HXX
#define LINKER_HXX

#include <iostream>
#include <vector>
#include "ast.hxx"

namespace linker {
    class Linker {
    public:
        Linker(ast::Program *);
        void addProgram(ast::Program *);
        friend std::ostream &operator <<(std::ostream &, const Linker &);
        void link();
    
    private:
        std::vector<Program *> m_programs;
        vector<uint8_t> m_bytecode;
    }; // class Linker
} // namespace linker

#endif // LINKER_HXX
