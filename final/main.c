#include <stdio.h>
#include "print.h"
#include "sem_print.h"

extern int syntax_err;
extern int semantic_err;
extern int gen_err;
extern A_NODE * root;
FILE * fout;

void semantic_analysis(A_NODE *);
void print_ast(A_NODE *);
void code_generation();

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
        printf("Error : syntax_error\n");
        return ;
    }
    print_ast(root);
    printf("print syntax\n");
    semantic_analysis(root);
    printf("semantic Analysis\n");
    
    if (semantic_err){
        printf("Error : semantic error\n");
        return ;
    }
    print_sem_ast(root);
    printf("print semantic\n");

    code_generation(root);
    printf("code_generation clear\n");
    
    if (gen_err){
        printf("Error : %d code generation error", gen_err);
        return ;
    }

}