%{
#include<stdio.h>
int a=0,b=0,c=0;
%}
%%
[Aa][a-zA-Z]* {a++;}
[Bb][a-zA-Z]* {b++;}
[Cc][a-zA-Z]* {c++;}
[a-zA-Z]+ ;
. ;
%%
int yywrap(){return 1;}
int main(){
printf("Enter text:\n");
yylex();
printf("Words starting with A=%d\n",a);
printf("Words starting with B=%d\n",b);
printf("Words starting with C=%d\n",c);
return 0;
}