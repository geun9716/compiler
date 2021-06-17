#include <stdio.h>
#include "print.h"
#include "sem_print.h"

extern int syntax_err;
extern int semantic_err;
extern int gen_err;
extern A_NODE * root;
FILE * fout;

void main() 
{

    if ((fout = fopen("a.asm", "w")) == NULL)
    {
        printf("can not open output file: a.asm\n");
        exit(1);
    }

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
    printf("print semantic\n");

    printf("code generation");
    code_generation(root);
    if (gen_err){
        printf("code generation error\n");
        return ;
    }
    printf("==========================");
    printf("Complete Code Generation\n");
}