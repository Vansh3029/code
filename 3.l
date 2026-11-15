%{
#include <stdio.h>
%}

%%

0[xX][0-9a-fA-F]+      { printf("%s : Hexadecimal Number\n", yytext); }

0[bB][01]+             { printf("%s : Binary Number\n", yytext); }

0[0-7]+                { printf("%s : Octal Number\n", yytext); }

[1-9][0-9]*|0          { printf("%s : Decimal Number\n", yytext); }

[ \t\n]+               ;

.                      { printf("%s : Invalid Input\n", yytext); }

%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter numbers (Press Ctrl+D on Linux / Ctrl+Z on Windows to stop):\n");
    yylex();
    return 0;
}