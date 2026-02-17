/* Input requirement
/* • Accept a character string, mix of text and numbers, from the user.
/* • Ensure the input is terminated with a newline character.

/*** Definition section ***/
%option noyywrap
%{
    #include <stdio.h>
%}

/*Rules Section */
%%
[0-9]+  {printf("%s\n",yytext);}
. {/*Ignore rest all symbols*/}
%%

/*** C Code section ***/
int main(void)
{
    printf("enter string:");
    yylex();
    return 0;
}