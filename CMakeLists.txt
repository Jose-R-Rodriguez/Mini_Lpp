cmake_minimum_required(VERSION 2.60)

project(lpp)

set( CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -std=c++14")

add_custom_command(
	OUTPUT lexer.cpp
	COMMAND re2c -c -o lexer.cpp ${PROJECT_SOURCE_DIR}/src/generators/lex.re
	MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/src/generators/lex.re
)

add_custom_command(
	OUTPUT parser.cpp
	COMMAND lemon -oparser.cpp -dparser.hpp -T${PROJECT_SOURCE_DIR}/src/lempar.c ${PROJECT_SOURCE_DIR}/src/generators/parser_gen_lemon.y
	MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/src/generators/parser_gen_lemon.y
)

add_custom_command(
	OUTPUT ast.cpp
	COMMAND treecc -o ast.cpp -h ast.hpp ${PROJECT_SOURCE_DIR}/src/generators/ast.tc
	MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/src/generators/ast.tc
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src/hdrs)
add_executable(lpp	parser.cpp
					lexer.cpp
					ast.cpp
					${PROJECT_SOURCE_DIR}/src/main.cpp)