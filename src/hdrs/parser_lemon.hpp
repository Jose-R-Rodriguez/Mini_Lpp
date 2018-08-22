#ifndef PARSER_LEMON_HPP
#define PARSER_LEMON_HPP
#include "parser.hpp"
void *ParseAlloc(void *(*mallocProc)(size_t));
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  const char* yyminor       /* The value for the token */
);
#endif