%{
#include <stdio.h>
int yylex();
int yyerror(char *s);
%}

%%
S: A '\n' { printf("Valid string\n"); }
 ;

A: 'a' A 'b'
 | 
 ;
%%

int main()
{
    printf("Enter a string: ");
    yyparse();
    return 0;
}

int yyerror(char *s)
{
    printf("Invalid string\n");
    return 0;
}