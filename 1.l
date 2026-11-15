%{
#include <stdio.h>
%}
%%
"if"|"else" {printf("%s\tKeyword\n", yytext);}
[a-zA-Z_][a-zA-Z0-9_]* {printf("%s\tIdentifier\n", yytext);}
[0-9]+ {printf("%s\tNumber\n", yytext);}
"<="|">="|"=="|"!="|"<"|">" {printf("%s\tRELOP\n", yytext);}
[ \t\n]+ ;
. {printf("%s\tUnknown\n", yytext);}
%%
int main() {
    printf("Enter a string:");
    yylex();
    return 0;
}
int yywrap() {
    return 1;
}