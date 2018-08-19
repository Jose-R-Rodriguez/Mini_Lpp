cmake_minimum_required(VERSION 2.60)

project(lpp)

set( CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS}")

add_custom_command(
  OUTPUT lexer.cpp
  COMMAND flex -o lexer.cpp ${PROJECT_SOURCE_DIR}/src/generators/lexer_gen.yy.l
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/src/generators/lexer_gen.yy.l)

add_custom_command(
  OUTPUT parser.cpp
  COMMAND bison -o parser.cpp ${PROJECT_SOURCE_DIR}/src/generators/parser_gen.y
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/src/generators/parser_gen.y)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src/hdrs)
add_executable(lpp	lexer.cpp
					parser.cpp
					src/main.cpp)