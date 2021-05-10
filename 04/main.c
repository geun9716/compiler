#include <stdio.h>
#include "print.h"
extern A_NODE * root;

void main() 
{
    initialize();
    printf("initialize\n");   
    yyparse();
    printf("Parse\n");
    print_ast(root);
}