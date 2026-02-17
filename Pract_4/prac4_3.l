/*** Definition section ***/
%option noyywrap
%{
    #include <stdio.h>
    int c=0,w=0,l=0,inword=0;
%}

/*** Rules section ***/
%%
\n {
     l++;
     c++;
     inword = 0;
   }

[ ] {
     c++;
     inword = 0;
   }

[A-Za-z] {
     c++;
     if (!inword) {
         w++;
         inword = 1;
     }
   }

. {
     c++;
   }
%%

/*** C Code section ***/
int main(void)
{
    FILE *file = fopen("input.txt","r");
    if(!file)
    {
        printf("Error in opening file");
        return 0;
    }

    yyin = file;
    yylex();
    fclose(file);

    printf("Lines: %d \nWords: %d \nCharacters: %d\n", l, w, c);
    return 0;
}