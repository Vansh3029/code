%{
#include <stdio.h>
int yylex();
int yyerror(char *s);
%}
%token DIGIT INVALID

%%
input:
    | input line
    ;

line:
      E '\n' { printf("Valid Expression Result = %d\n", $1); }
    | '\n'
    ;

E : E '+' T { $$ = $1 + $3; }
  | T       { $$ = $1; }
  ;

T : T '*' F { $$ = $1 * $3; }
  | F       { $$ = $1; }
  ;

F : '(' E ')' { $$ = $2; }
  | DIGIT     { $$ = $1; }
  ;
%%

int yyerror(char *s) {
    printf("Invalid Expression\n");
    return 0;
}

int main() {
    printf("Enter expressions (Ctrl+D to stop):\n");
    yyparse();
    return 0;
}