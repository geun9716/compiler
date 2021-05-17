#include <stdio.h>
#include "print.h"
extern int syntax_err;
extern A_NODE * root;

void main() 
{
    initialize();
    printf("initialize\n");
    yyparse();
    printf("parse\n");
    print_ast(root);
    printf("Done\n");
}