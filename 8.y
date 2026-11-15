%{
#include <stdio.h>
int yylex();
int yyerror(char *s);
%}

%token NUMBER INVALID

%%
input:
      expr { printf("Valid arithmetic expression!\n"); }
    ;

expr:
      NUMBER
    | expr '+' NUMBER
    | expr '-' NUMBER
    ;
%%

int yyerror(char *s)
{
    printf("Invalid arithmetic expression!\n");
    return 0;
}

int main()
{
    printf("Enter an arithmetic expression: ");
    yyparse();
    return 0;
}
