#include <stdio.h>
#include "print.h"
#include "sem_print.h"

extern int syntax_err;
extern int semantic_err;
extern A_NODE * root;


void main() 
{
    initialize();
    printf("initialize\n");
    yyparse();
    printf("parse\n");
    if (syntax_err){
        printf("syntax_error\n");
        return ;
    }
    print_ast(root);
    printf("print syntax\n");
    semantic_analysis(root);
    printf("semantic Analysis\n");
    
    if (semantic_err){
        printf("semantic_error\n");
        return ;
    }
    print_sem_ast(root);
}