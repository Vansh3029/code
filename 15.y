
%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(char *s);
%}

%union {
    int num;
    char *str;
}

%token REPEAT TIMES OPEN CLOSE PRINT
%token <num> NUM
%token <str> STRING

%%

program:
    REPEAT NUM TIMES OPEN PRINT STRING CLOSE
    {
        for (int i = 0; i < $2; i++)
            printf("%s\n", $6);

        free($6);
    }
    ;

%%

void yyerror(char *s)
{
    printf("Invalid syntax\n");
}

int main()
{
    printf("Enter program:\n");
    yyparse();
    return 0;
}
