%option noyywrap
%option reentrant
%{
#define YY_INPUT(buf, result, max_size)\

#define YY_DECL

%}

%%
"programa"	{}
%%