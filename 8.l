%{
#include "y.tab.h"
%}

%%
[0-9]+      { return NUMBER; }
[+\-]       { return yytext[0]; }
[ \t\n]+    ;
.           { return INVALID; }
%%

int yywrap()
{
    return 1;
}
