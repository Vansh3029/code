%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(const char *s);
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
    | expr '/' expr     {
                            if ($3 == 0) {
                                printf("Division by zero error\n");
                                YYERROR;
                            }
                            $$ = $1 / $3;
                        }
    | '(' expr ')'      { $$ = $2; }
    | '-' expr %prec UMINUS { $$ = -$2; }
    ;
%%

void yyerror(const char *s)
{
    printf("Invalid arithmetic expression!\n");
}

int main()
{
    printf("Enter an arithmetic expression: ");
    yyparse();
    return 0;
}