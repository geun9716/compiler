#include "type.h"

void semantic_analysis(A_NODE *);
void sem_program(A_NODE *);
int sem_declaration_list(A_ID *, int);
int sem_declaration(A_ID *, int);
int sem_A_TYPE(A_TYPE *);
A_TYPE * sem_expression(A_NODE *);
int sem_statement(A_NODE*, int);
int sem_statement_list(A_NODE*, int);
void sem_for_expression(A_NODE *);
A_TYPE * sem_initializer(A_NODE *);
A_ID * sem_arg_expr_list(A_NODE *, A_ID *);
A_ID * getStructFieldIdentifier(A_TYPE *, char *);
A_ID * getPointerFieldIdentifier(A_TYPE *, char *);
A_NODE * convertScalarToInteger(A_NODE *);
A_NODE * convertUsualAssignmentConversion(A_TYPE *, A_NODE *);
A_NODE * convertUsualUnaryConversion(A_NODE *);
A_TYPE * convertUsualBinaryConversion(A_NODE *);
A_NODE * convertCastingConversion(A_NODE *, A_TYPE *);
BOOLEAN isAllowableAssignmentConversion(A_TYPE *, A_TYPE *, A_NODE *);
BOOLEAN isAllowableCastingConversion(A_TYPE *, A_TYPE *);
BOOLEAN isModifiableLvalue(A_NODE *);
BOOLEAN isConstantZeroExp(A_NODE *);
BOOLEAN isSameParameterType(A_ID *, A_ID *);
BOOLEAN isCompatibleType(A_TYPE *, A_TYPE *);
BOOLEAN isCompatiblePointerType(A_TYPE *, A_TYPE *);
BOOLEAN isIntType(A_TYPE *);
BOOLEAN isFloatType(A_TYPE *);
BOOLEAN isArithmeticType(A_TYPE *);
BOOLEAN isScalarType(A_TYPE *);
BOOLEAN isAnyIntegerType(A_TYPE *);
BOOLEAN isIntegralType(A_TYPE *);
BOOLEAN isStructOrUnionType(A_TYPE *);
BOOLEAN isFunctionType(A_TYPE *);
BOOLEAN isPointerType(A_TYPE *);
BOOLEAN isPointerOrArrayType(A_TYPE *);
BOOLEAN isArrayType(A_TYPE *);
BOOLEAN isStringType(A_TYPE *);
BOOLEAN isVoidType(A_TYPE *);
A_LITERAL checkTypeAndConvertLiteral(A_LITERAL, A_TYPE*);
A_LITERAL getTypeAndValueOfExpression(A_NODE *);
void semantic_warning(int, int);
void semantic_error();
int put_literal(A_LITERAL);
void set_literal_address(A_NODE *);

void semantic_analysis(A_NODE *node)
{
    sem_program(node);
    set_literal_address(node);
}
void sem_program(A_NODE * node)
{
    switch(node->name){
        case N_PROGRAM:
            sem_declaration_list(node->clink, 12);
            node->value=global_address;
            break;
    }
}
int sem_declaration_list(A_ID * id, int addr)
{
    int i = addr;
    while(id){
        addr += sem_declaration(id, addr);
        id = id->link;
    }
    return (addr-i);
}
int sem_declaration(A_ID * id, int addr)
{
    A_TYPE *t;
    int result = 0, i;
    A_LITERAL lit;
    
}
int sem_A_TYPE(A_TYPE *)
A_TYPE * sem_expression(A_NODE *)
int sem_statement(A_NODE*, int)
int sem_statement_list(A_NODE*, int)
void sem_for_expression(A_NODE *)
A_TYPE * sem_initializer(A_NODE *)
A_ID * sem_arg_expr_list(A_NODE *, A_ID *)
A_ID * getStructFieldIdentifier(A_TYPE *, char *)
A_ID * getPointerFieldIdentifier(A_TYPE *, char *)
A_NODE * convertScalarToInteger(A_NODE *)
A_NODE * convertUsualAssignmentConversion(A_TYPE *, A_NODE *)
A_NODE * convertUsualUnaryConversion(A_NODE *)
A_TYPE * convertUsualBinaryConversion(A_NODE *)
A_NODE * convertCastingConversion(A_NODE *, A_TYPE *)
BOOLEAN isAllowableAssignmentConversion(A_TYPE *, A_TYPE *, A_NODE *)
BOOLEAN isAllowableCastingConversion(A_TYPE *, A_TYPE *)
BOOLEAN isModifiableLvalue(A_NODE *)
BOOLEAN isConstantZeroExp(A_NODE *)
BOOLEAN isSameParameterType(A_ID *, A_ID *)
BOOLEAN isCompatibleType(A_TYPE *, A_TYPE *)
BOOLEAN isCompatiblePointerType(A_TYPE *, A_TYPE *)
BOOLEAN isIntType(A_TYPE *)
BOOLEAN isFloatType(A_TYPE *)
BOOLEAN isArithmeticType(A_TYPE *)
BOOLEAN isScalarType(A_TYPE *)
BOOLEAN isAnyIntegerType(A_TYPE *)
BOOLEAN isIntegralType(A_TYPE *)
BOOLEAN isStructOrUnionType(A_TYPE *)
BOOLEAN isFunctionType(A_TYPE *)
BOOLEAN isPointerType(A_TYPE *)
BOOLEAN isPointerOrArrayType(A_TYPE *)
BOOLEAN isArrayType(A_TYPE *)
BOOLEAN isStringType(A_TYPE *)
BOOLEAN isVoidType(A_TYPE *)
A_LITERAL checkTypeAndConvertLiteral(A_LITERAL, A_TYPE*)
A_LITERAL getTypeAndValueOfExpression(A_NODE *)
void semantic_warning(int, int)
void semantic_error()
int put_literal(A_LITERAL)
void set_literal_address(A_NODE *)
