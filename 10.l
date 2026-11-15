%{
#include "y.tab.h"
%}

%%
[01]+       { yylval = atoi(yytext); return BIN; }
[ \t]       ;
\n          { return '\n'; }
.           { return yytext[0]; }
%%

int yywrap()
{
    return 1;
}