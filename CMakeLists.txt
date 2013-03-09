project(asm)
cmake_minimum_required(VERSION 2.8)

set(SOURCES 
    ast.cxx
    lexer.cxx
    opcodes.cxx
    parser.cxx)

add_executable(asm ${SOURCES})
