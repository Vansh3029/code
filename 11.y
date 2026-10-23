%{
#include <stdio.h>
#include<stdlib.h>
int yylex();
int yyerror(char *s);
%}

%token NUM
%left '+' '-'
%left '*' '/'
%right UMINUS

%%
input:
    expr '\n' { printf("Result = %d\n", $1); }
    ;

expr:
    NUM                 { $$ = $1; }
    | expr '+' expr     { $$ = $1 + $3; }
    | expr '-' expr     { $$ = $1 - $3; }
    | expr '*' expr     { $$ = $1 * $3; }
    | expr '/' expr     { $$ = $1 / $3; }
    | '(' expr ')'      { $$ = $2; }
    | '-' expr %prec UMINUS { $$ = -$2; }
    ;
%%

int main()
{
    printf("Enter an arithmetic expression: ");
    yyparse();
    return 0;
}

int yyerror(char *s)
{
    printf("Invalid arithmetic expression!\n");
    return 0;
}