%{
#include <stdio.h>

int lines = 0, spaces = 0, words = 0;
%}

%%
\n          {lines++;}

[ ]         {spaces++;}

[^ \t\n]+   {words++;}

\t          {spaces++;}
%%

int main() {
    printf("Enter the text (Press Ctrl+D to stop):\n");
    yylex();

    printf("\nNumber of lines: %d\n", lines);
    printf("Number of spaces: %d\n", spaces);
    printf("Number of words: %d\n", words);

    return 0;
}

int yywrap() {
    return 1;
}
