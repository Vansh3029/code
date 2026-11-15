%{
#include<stdio.h>
#include<string.h>

char longest[100];
int maxlen=0;

%}

%%
[a-zA-Z]+ {
    if(yyleng>maxlen)
    {
        maxlen=yyleng;
        strcpy(longest,yytext);
    }
}
\n {
    printf("Longest string: %s\n",longest);
    printf("Length: %d\n",maxlen);
    return 0;
}
. ;
%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter strings: ");
    yylex();
    return 0;
}