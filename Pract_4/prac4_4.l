%option noyywrap
%{
#include <stdio.h>
#include <ctype.h>
%}

%%

[a-zA-Z0-9*;#$@]+ {
    int l=0,u=0,d=0,s=0;
    int len = yyleng;

    if(len < 9 || len > 15) {
        printf("Invalid password\n");
        return 0;
    }

    for(int i=0;i<len;i++) {
        char c = yytext[i];
        if(islower(c)) l=1;
        else if(isupper(c)) u=1;
        else if(isdigit(c)) d=1;
        else if(c=='*'||c==';'||c=='#'||c=='$'||c=='@') s=1;
    }

    if(l && u && d && s)
        printf("Valid password\n");
    else
        printf("Invalid password\n");
}

. {
    printf("Invalid password\n");
}

%%

int main() {
    yylex();
    return 0;
}
