%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void yyerror(const char *s);
int yylex();
%}

%union {
    double dval;
}

%token <dval> DIGIT
%type <dval> E T F G

%%
// L -> E n
L : E '\n' { printf("Result: %g\n\n", $1); }
  ;

// E -> E + T | E - T | T
E : E '+' T { $$ = $1 + $3; }
  | E '-' T { $$ = $1 - $3; }
  | T       { $$ = $1; }
  ;

// T -> T * F | T / F | F
T : T '*' F { $$ = $1 * $3; }
  | T '/' F { 
        if($3 == 0) { printf("Error: Division by zero\n"); exit(1); }
        else $$ = $1 / $3; 
    }
  | F       { $$ = $1; }
  ;

// F -> G ^ F | G (Right associative exponentiation)
F : G '^' F { $$ = pow($1, $3); }
  | G       { $$ = $1; }
  ;

// G -> ( E ) | digit
G : '(' E ')' { $$ = $2; }
  | DIGIT     { $$ = $1; }
  ;

%%

void yyerror(const char *s) {
    printf("Invalid expression\n");
    exit(0);
}

int main() {
    printf("Enter expression: ");
    yyparse();
    return 0;
}