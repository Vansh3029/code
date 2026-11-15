%{
#include <stdio.h>
#include <ctype.h>

int yylex();
int yyerror(char *s);

char production[10][10];
int n, p;

void findFirst(char c)
{
    int i;

    if (!isupper(c))
    {
        printf("%c ", c);
        return;
    }

    for (i = 0; i < n; i++)
    {
        if (production[i][0] == c)
        {
            if (production[i][2] == '$')
                printf("$ ");

            else if (!isupper(production[i][2]))
                printf("%c ", production[i][2]);

            else
                findFirst(production[i][2]);
        }
    }
}
%}

%union {
    char ch;
}

%token <ch> NONTERM

%%

input:
      NONTERM
      {
          printf("FIRST(%c) = { ", $1);
          findFirst($1);
          printf("}\n");
      }
    | input NONTERM
      {
          printf("FIRST(%c) = { ", $2);
          findFirst($2);
          printf("}\n");
      }
    ;

%%

int main()
{
    int i;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter number of non-terminals: ");
    scanf("%d", &p);

    printf("Enter productions (Example: E=aA):\n");

    for (i = 0; i < n; i++)
        scanf("%s", production[i]);

    printf("Enter non-terminals:\n");

    yyparse();

    return 0;
}

int yyerror(char *s)
{
    printf("Invalid input\n");
    return 0;
}
