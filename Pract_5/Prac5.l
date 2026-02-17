/*** Definition section ***/
%{
#include <stdio.h>
int line = 1;
FILE *yyin;
%}

/*RULES SECTION*/
%%
int|char|float|double|long|short|void|return|struct { printf("Keyword: %s\n", yytext); }

[0-9]+[a-zA-Z]+ { printf("Line %d : %s invalid lexeme\n", line, yytext); }

[0-9]+ { printf("Numeric Constant: %s\n", yytext); }
\'[^\']\' { printf("Character Constant: %s\n", yytext); }

\"[^\"]*\" { printf("String: %s\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]* { printf("Identifier: %s\n", yytext); }

=|\+|\-|\*|\/|% { printf("Operator: %s\n", yytext); }

,|;|\(|\)|\{|\} { printf("Punctuation: %s\n", yytext); }

"//".*      { }
"/*"(.|\n)*"*/" { }

\n      { line++; }

[ \t]   { }

. { printf("Line %d : %s invalid character\n", line, yytext); }

%%

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("No input file is provided to parse.\n");
        return 1;
    }
    yyin = fopen(argv[1], "r");
    if(yyin == NULL)
    {
        printf("Cannot open file.\n");
        return 1;
    }

    printf("TOKENS\n");
    yylex();
    return 0;
}