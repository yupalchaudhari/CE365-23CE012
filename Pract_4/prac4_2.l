/*** Definition section ***/
%option noyywrap
%{
    #include <stdio.h>
%}

/*** Rules section ***/
%%
"charusat" {printf("university");}
. {printf("%s",yytext);}
%%

/*** C Code section ***/
int main(void)
{
    yylex();
    return 0;
}