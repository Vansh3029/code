%{
#include "y.tab.h"
#include <stdlib.h>
%}
%%
[0-9]+      { yylval = atoi(yytext); return DIGIT; }
[+*()]      { return yytext[0]; }
[ \t]+      ;
\n          { return '\n'; }
.           { return INVALID; }
%%
int yywrap() {
    return 1;
}