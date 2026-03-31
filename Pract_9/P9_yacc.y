%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token IF COND THEN ELSE ATOMIC

%%

lines : lines line
      | line
      ;

line  : S '\n' { printf("Valid string\n\n"); }
      | '\n'   { }
      | error '\n' { yyerrok; } 
      ;

S   : IF E THEN S S_prime
    | ATOMIC
    ;

S_prime : ELSE S
        | /* epsilon */
        ;

E   : COND
    ;

%%

void yyerror(const char *s) {
    printf("Invalid string\n\n");
}

int main() {
    printf("Enter strings:\n");
    yyparse();
    return 0;
}