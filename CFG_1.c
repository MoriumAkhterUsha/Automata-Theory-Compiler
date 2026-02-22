// CFG(Context Free Grammar): S → aSb | ε

//scanner.l
%{
#include "parser.tab.h"
#include <stdio.h>
%}

%%
[a|b]+      { yylval.sval = yytext; return STRING; }
\n          ;
.           { return INVALID; }
%%

int yywrap() { return 1; }

//parser.y
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);

int yyparse_string(const char *s);
int parse_S(const char *s, int *i, int len);
%}

%union {
    char* sval;
}

%token <sval> STRING
%token INVALID

%%
input:
    STRING  {
                printf("Input String: %s\n", $1);
                printf("Parsing result: ");
                if (yyparse_string($1))
                    printf("String is accepted.\n");
                else
                    printf("Syntax error.\n");
            }
    | INVALID { printf("Invalid Input\n"); }
    ;
%%

int main() {
    printf("Enter string: ");
    return yyparse();
}

// CFG: S → aSb | ε
int yyparse_string(const char *s) {
    int i = 0;
    int len = strlen(s);

    if (parse_S(s, &i, len) && i == len)
        return 1; // Accepted if entire string parsed
    else
        return 0; // Otherwise rejected
}

// Recursive function to simulate CFG rule S → aSb | ε
int parse_S(const char *s, int *i, int len) {
    if (*i < len && s[*i] == 'a') {
        (*i)++;
        if (!parse_S(s, i, len)) return 0;
        if (*i < len && s[*i] == 'b') {
            (*i)++;
            return 1;
        }
        return 0;
    }
    return 1; // ε
}

void yyerror(const char *s) {
    printf("Error: %s\n", s);
}

