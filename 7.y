%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
int yyerror(char *s);
%}

%token SOUND PLACE INVALID

%%
input:
      SOUND  { printf("Sound: A vibration that travels through a medium as a wave.\n"); }
    | PLACE  { printf("Place: A particular position or location.\n"); }
    | INVALID { printf("Invalid word!\n"); }
    ;
%%

int yyerror(char *s)
{
    printf("Invalid input!\n");
    return 0;
}

int main()
{
    printf("Enter sound or place: ");
    yyparse();
    return 0;
}
