%{
#include "y.tab.h"
%}

%%
sound       { return SOUND; }
place       { return PLACE; }
[ \t\n]+    ;
[a-zA-Z]+ { return INVALID; }
[0-9]+ { return INVALID; }
%%

int yywrap()
{
    return 1;
}
