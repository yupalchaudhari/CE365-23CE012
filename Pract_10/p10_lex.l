%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%
[0-9]+(\.[0-9]+)? { yylval.dval = atof(yytext); return DIGIT; }
"+"               { return '+'; }
"-"               { return '-'; }
"*"               { return '*'; }
"/"               { return '/'; }
"^"               { return '^'; }
"("               { return '('; }
")"               { return ')'; }
[ \t]             { /* skip whitespace */ }
\n                { return '\n'; }
.                 { return yytext[0]; }
%%

int yywrap() {
    return 1;
}