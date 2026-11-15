%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(char *s);
%}

%token BIN

%%
input : BIN '\n' {
    int n = yylval;
    int decimal = 0, base = 1;

    while(n > 0)
    {
        decimal += (n % 10) * base;
        base *= 2;
        n /= 10;
    }

    printf("Decimal = %d\n", decimal);
}
;
%%

int main()
{
    printf("Enter a binary number: ");
    yyparse();
    return 0;
}

int yyerror(char *s)
{
    printf("Invalid binary number\n");
    return 0;
}