project(asm)
cmake_minimum_required(VERSION 2.8)

set(SOURCES 
    ast.cxx
    lexer.cxx
    opcodes.cxx
    parser.cxx)

set(HEADERS
	ast.hxx
	lexer.hxx
	linker.hxx
	opcodes.hxx
	parser.hxx)
	
add_executable(asm ${SOURCES} ${HEADERS})
