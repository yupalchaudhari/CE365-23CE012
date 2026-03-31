%{
#include "y.tab.h"
%}

%%
"i"         { return IF; }
"b"         { return COND; }
"t"         { return THEN; }
"e"         { return ELSE; }
"a"         { return ATOMIC; }
[ \t]       { /* ignore spaces and tabs, but NOT newlines */ }
"\n"        { return '\n'; }
.           { return yytext[0]; }
%%

int yywrap() {
    return 1;
}