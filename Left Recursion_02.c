/*Write a Lex and Yacc program that takes a context-free grammar as input and
identifies whether the grammar contains left recursion, right recursion, or neither
recursion.*/

#include <stdio.h>
#include <string.h>

#define MAX 10
#define MAXLEN 100

struct Production {
    char nonTerminal;
    char rhs[MAX][MAXLEN];
    int count;
};

int main() {
    int n;
    struct Production p[MAX];
    char temp[MAXLEN];
    printf("Enter number of productions: ");
    scanf("%d", &n);
    getchar(); // clear newline

    // Input productions
    for (int i = 0; i < n; i++) {
        printf("Enter production %d (Example: E->E+T|T): ", i + 1);
        fgets(temp, sizeof(temp), stdin);
        temp[strcspn(temp, "\n")] = '\0'; // remove newline

        p[i].nonTerminal = temp[0];
        p[i].count = 0;

        // Split RHS parts by '|'
        char *rhsPart = strtok(temp + 3, "|");
        while (rhsPart != NULL) {
            strcpy(p[i].rhs[p[i].count++], rhsPart);
            rhsPart = strtok(NULL, "|");
        }
    }

    printf("\nAnalyzing Grammar...\n");

    for (int i = 0; i < n; i++) {
        int hasLeftRecursion = 0;
        int hasRightRecursion = 0;

        for (int j = 0; j < p[i].count; j++) {
            if (p[i].rhs[j][0] == p[i].nonTerminal)
                hasLeftRecursion = 1;
            int len = strlen(p[i].rhs[j]);
            if (p[i].rhs[j][len - 1] == p[i].nonTerminal)
                hasRightRecursion = 1;
        }

        printf("\nProduction %c:\n", p[i].nonTerminal);
        if (hasLeftRecursion)
            printf("  -> Left Recursive detected\n");
        if (hasRightRecursion)
            printf("  -> Right Recursive detected\n");
        if (!hasLeftRecursion && !hasRightRecursion)
            printf("  -> No recursion detected.\n");



    }

    return 0;
}
