%{
#include "y.tab.h"
%}

%%

[A-Z]       {
                yylval.ch = yytext[0];
                return NONTERM;
            }

[ \t\n]+    ;

.           ;

%%

int yywrap()
{
    return 1;
}
