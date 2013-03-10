#ifndef LINKER_HXX
#define LINKER_HXX

#include <iostream>
#include <vector>
#include "ast.hxx"

namespace linker {
    class Linker {
    public:
        Linker();
        void addProgram(ast::Program *);
        friend std::ostream &operator <<(std::ostream &, const Linker &);
        void link();
    
    private:
        std::vector<Program *> m_programs;
        DataBuffer m_rodata;
        DataBuffer m_data;
        CodeBuffer m_text;
    }; // class Linker
} // namespace linker

#endif // LINKER_HXX
