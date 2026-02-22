//scanner.l
%{
#include "parser.tab.h"
%}

%%
0       { return ZERO; }
1       { return ONE; }
[ \t\r\n]+   ;   /* ignore whitespace */
.       { printf("Invalid character: %s\n", yytext); exit(1); }
%%

int yywrap() {
    return 1;
}

//parser.y
%{
#include <stdio.h>
#include <stdlib.h>

// Define DFA states
typedef enum { S0, S1 } State;

State current_state = S0;

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int yylex(void);
%}

%token ZERO ONE

%%
input:
    sequence
    {
        if (current_state == S1)
            printf("Accepted: The string ends with '1'.\n");
        else
            printf("Rejected: The string does not end with '1'.\n");
        exit(0);
    }
;
sequence:
    /* empty */
    | sequence ZERO {
        // Transition from current state on input '0'
        switch(current_state) {
            case S0: current_state = S0; break;
            case S1: current_state = S0; break;
        }
    }
    | sequence ONE {
        // Transition from current state on input '1'
        switch(current_state) {
            case S0: current_state = S1; break;
            case S1: current_state = S1; break;
        }
    }
;
%%

int main() {
    printf("Enter a binary string (only 0 and 1):\n");
    yyparse();
    return 0;
}

