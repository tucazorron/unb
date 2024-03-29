%option noyywrap
%option outfile="./output/lexical.c" header-file="./output/lexical.h"

/* definições */

%{
#include <stdio.h>
#include <string.h>

#include "parser.tab.h"

static int next_column = 1;
int column = 1;
#define NEXT_CHAR_NUMBER ; column += yyleng;
%}

/*analisador léxico */

Number [0-9]
Char [a-zA-Z]
Sign [+-]

identifier  ({Char}|_)({Number}|{Char}|_)*
int         {Sign}?{Number}+

%%
[ \t]+      { column+= yyleng; }
\n          { yylineno++; column = 1; }
"if"        { NEXT_CHAR_NUMBER; return IF; }
"else"      { NEXT_CHAR_NUMBER; return ELSE; }
"while"     { NEXT_CHAR_NUMBER; return WHILE; }
"return"    { NEXT_CHAR_NUMBER; return RETURN; }
"void"      { NEXT_CHAR_NUMBER; return VOID; }
"int"       { NEXT_CHAR_NUMBER; return INT; }

">" { NEXT_CHAR_NUMBER; return GREATER; }
">=" { NEXT_CHAR_NUMBER; return GE; }
"<" { NEXT_CHAR_NUMBER; return LOWER; }
"<=" { NEXT_CHAR_NUMBER; return LE; }
"==" { NEXT_CHAR_NUMBER; return EQ; }
"!=" { NEXT_CHAR_NUMBER; return NE; }
"=" { NEXT_CHAR_NUMBER; return ASSIGN; }
"+" { NEXT_CHAR_NUMBER; return SUM; }
"-" { NEXT_CHAR_NUMBER; return MINUS; }
"*" { NEXT_CHAR_NUMBER; return TIMES; }
"/" { NEXT_CHAR_NUMBER; return DIVIDE; }
"(" { NEXT_CHAR_NUMBER; return '('; }
")" { NEXT_CHAR_NUMBER; return ')'; }
"{" { NEXT_CHAR_NUMBER; return '{'; }
"}" { NEXT_CHAR_NUMBER; return '}'; }
";" { NEXT_CHAR_NUMBER; return ';'; }
"[" { NEXT_CHAR_NUMBER; return '['; }
"]" { NEXT_CHAR_NUMBER; return ']'; }
"," { NEXT_CHAR_NUMBER; return ','; }

{int}           { NEXT_CHAR_NUMBER; yylval.integer = atoi (yytext); return INTEGER; }
{identifier}    { NEXT_CHAR_NUMBER; yylval.string = strdup (yytext); return ID; }

%%