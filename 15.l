
%{
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%x MESSAGE

%%

[Rr][Ee][Pp][Ee][Aa][Tt]   { return REPEAT; }
[Tt][Ii][Mm][Ee][Ss]       { return TIMES; }
[Pp][Rr][Ii][Nn][Tt]       { BEGIN(MESSAGE); return PRINT; }

"<<"           { return OPEN; }
">>"           { return CLOSE; }

<INITIAL>"<"[0-9]+">" {
    yylval.num = atoi(yytext + 1);
    return NUM;
}

<MESSAGE>[ \t]+  ;

<MESSAGE>"<"[^>\n]*">" {
    int len = yyleng - 2;
    yylval.str = malloc(len + 1);
    strncpy(yylval.str, yytext + 1, len);
    yylval.str[len] = '\0';
    BEGIN(INITIAL);
    return STRING;
}

[ \t\n]+       ;

.              { return yytext[0]; }

%%

int yywrap()
{
    return 1;
}
