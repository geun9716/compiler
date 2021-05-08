
%{
    #include "yaccsupfunc.h"
    #include "type.h"
    extern int line_no, syntax_err;
    extern A_NODE *root;
    extern A_ID *current_id;
    extern int current_level;
    extern A_TYPE * int_type;
%}

%start program
%token	IDENTIFIER TYPE_IDENTIFIER FLOAT_CONSTANT INTEGER_CONSTANT CHARACTER_CONSTANT STRING_LITERAL

		AUTO_SYM STATIC_SYM TYPEDEF_SYM STRUCT_SYM ENUM_SYM SIZEOF_SYM UNION_SYM IF_SYM ELSE_SYM
		WHILE_SYM DO_SYM FOR_SYM CONTINUE_SYM BREAK_SYM RETURN_SYM SWITCH_SYM CASE_SYM DEFAULT_SYM

		PLUS MINUS PLUSPLUS MINUSMINUS BAR AMP BARBAR AMPAMP STAR SLASH PERCENT ASSIGN
		ARROW COLON SEMICOLON DOTDOTDOT PERIOD COMMA EXCL 
		LSS GTR LEQ GEQ EQL NEQ LP RP LB RB LR RR

%%

program:
    translation_unit                                        {root=makeNode(N_PROGRAM, NIL, $1, NIL); checkForwardReference();}
    ;

translation_unit:
    external_declaration                                    {$$=$1;}
    |translation_unit external_declaration                  {$$=linkDeclaratorList($1,$2);}
    ;

external_declaration:                       
    function_definition                                     {$$=$1;}
    |declaration                                            {$$=$1;}
    ;

function_definition:
    declaration_specifiers declarator compound_statement    {$$=setFunctionDeclaratorSpecifier($2, $1);}    
    |declarator compound_statement                          {$$=setFunctionDeclaratorBody($3, $3);}
    ;

declaration_list_opt:
                                                            {$$=NIL;}
    |declaration_list                                       {$$=$1;}
    ;

declaration_list:
    declaration                                             {$$=$1;}
    |declaration_list declaration                           {$$=linkDeclaratorList($1, $2);}
    ;

declaration:
    declaration_specifiers init_declarator_list_opt SEMICOLON   {$$=setDeclaratorListSpecifier($2, $1);}
    ;

declaration_specifiers:
    type_specifier                                          {$$=makeSpecifier($1, 0);}
    |storage_class_specifier                                {$$=makeSpecifier(0, $1);}
    |type_specifier declaration_specifiers                  {$$=updateSpecifier($2, $1, 0);}
    |storage_class_specifier declaration_specifiers         {$$=updateSpecifier($1, 0, $2;)}
    ;

storage_class_specifier:
    AUTO_SYM                                                {$$=S_AUTO;}
    |STATIC_SYM                                             {$$=S_STATIC;}
    |TYPEDEF_SYM                                            {$$=S_TYPEDEF;}
    ;

init_declarator_list_opt:
                                                            {$$=NIL;}
    |init_declarator_list                                   {$$=$1;}
    ;

init_declarator_list:
    init_declarator                                         {$$=$1;}
    |init_declarator_list COMMA init_declarator             {$$=linkDeclaratorList($1,$3);}
    ;

init_declarator:
    declarator                                              {$$=$1;}
    |declarator ASSIGN initializer                          {$$=setDeclaratorInit($1,$3);}
    ;

initializer:
    constant_expression                                     {$$=makeNode(N_INIT_LIST_ONE,NIL,$1,NIL);}
    |LR initializer_list RR                                 {$$=$2;}
    ;

initializer_list:
    initializer                                             {$$=makeNode(N_INIT_LIST, $1, NIL, makeNode(N_INIT_LIST_NIL, NIL, NIL, NIL));}
    |initializer_list COMMA initializer                     {$$=makeNodeList(N_INIT_LIST, $1, $3);}
    ;

type_specifier:
    struct_type_specifier                                   {$$=$1;}
    |enum_type_specifier                                    {$$=$1;}
    |TYPE_IDENTIFIER                                        {$$=$1;}
    ;

struct_type_specifier:
    struct_or_union IDENTIFIER {$$=setTypeStructOrEnumIdentifier($1,$2,ID_STRUCT);} LR {$$=current_id; current_level++;} struct_declaration_list RR {checkForwardReference(); $$=setTypeField($3, $6); current_level--; current_id=$1;}
    |struct_or_union {$$=makeType($1);} LR ($$=current_id;current_level++;) struct_declaration_list RR {checkForwardReference(); $$=setTypeField($2, $5); current_level++; current_id=$4;}
    |struct_or_union IDENTIFIER {$$=getTypeStructOrEnumRefIdentifier($1, $2, ID_STRUCT);}
    ;

struct_or_union:
    STRUCT_SYM  {$$=T_STRUCT;}
    |UNION_SYM  {$$=T_UNION;}
    ;

struct_declaration_list:
    struct_declaration                                      {$$=$1;}
    |struct_declaration_list struct_declaration             {$$=linkDeclaratorList($1, $2);}
    ;

struct_declaration:
    type_specifier struct_declarator_list SEMICOLON         {$$=setStructDeclaratorListSpecifier($2, $1);}
    ;

struct_declarator_list:
    struct_declarator                                       {$$=$1;}
    |struct_declarator_list COMMA struct_declarator         {$$=linkDeclaratorList($1, $3);}
    ;

struct_declarator:
    declarator                                              {$$=$1;}
    ;

enum_type_specifier:
    ENUM_SYM IDENTIFIER {$$=setTypeStructOrEnumIdentifier(T_ENUM, $2, ID_ENUM);} LR enumerator_list RR {$$=setTypeField($3,$5);}               
    |ENUM_SYM {$$=makeType(T_ENUM);} LR enumerator_list RR {$$=setTypeField($2, $4);} 
    |ENUM_SYM IDENTIFIER {$$=getTypeOfStructOrEnumRefIdentifier(T_ENUM, $2, ID_ENUM);}
    ;

enumerator_list:
    enumerator {$$=$1;}
    |enumerator_list COMMA enumerator {$$=linkDeclaratorList($1,$3);}
    ;

enumerator:
    IDENTIFIER {$$=setDeclaratorKind(makeIdentifier($1), ID_ENUM_LITERAL);}
    |IDENTIFIER {$$=setDeclaratorKind(makeIdentifier($1), ID_ENUM_LITERAL);} ASSIGN expression {$$=setDeclaratorInit($2, $4);} 
    ;

declarator:
    pointer direct_declarator {$$=setDeclaratorElementType($2, $1);}
    |direct_declarator {$$=$1;}
    ;

pointer:
    STAR {$$=makeType(T_POINTER);}
    |STAR pointer {$$=setTypeElementType($2, makeType(T_POINTER));}
    ;

direct_declarator:
    IDENTIFIER {$$=makeIdentifier($1);}
    |LP declarator RP {$$=$2;}
    |direct_declarator LB constant_expression_opt RB {$$=setDeclaratorElementType($1, setTypeExpr(makeType(T_ARRAY), $3));} 
    |direct_declarator LP {$$=current_id; current_level++} parameter_type_list_opt RP {checkForwardReference(); current_id = $3; current_level--; $$=setDeclaratorElementType($1, setTypeField(makeType(T_FUNC), $4));} 
    ;

parameter_type_list_opt:
                                    {$$=NIL;}
    |parameter_type_list            {$$=$1;}
    ;

parameter_type_list:
    parameter_list {$$=$1;}
    |parameter_list COMMA DOTDOTDOT {$$=linkDeclaratorList($1, setDeclaratorKind(makeDummyIdentifier(), ID_PARM));}
    ;

parameter_list:
    parameter_declaration {$$=$1;}
    |parameter_list COMMA parameter_declaration {$$=linkDeclaratorList($1, $3);}
    ;

parameter_declaration:
    declaration_specifiers declarator {$$=setParameterDeclaratorSpecifier($2, $1);}
    |declaration_specifiers abstract_declarator_opt {$$=setParameterDeclaratorSpecifier(setDeclaratorType(makeDummyIdentifier(), $2), $1);}
    ;

abstract_declarator_opt:
                                    {$$=NIL;}
    |abstract_declarator            {$$=$1;}
    
abstract_declarator:
    direct_abstract_declarator      {$$=$1}
    |pointer                        {$$=makeType(T_POINTER);}
    |pointer direct_abstract_declarator {$$=setTypeElementType($2, makeType(T_POINTER));}
    ;

direct_abstract_declarator:
    LP abstract_declarator RP {$$=$2;}
    |LB constant_expression_opt RB {$$=setTypeExpr(makeType(T_ARRAY), $2);}
    |direct_abstract_declarator LB constant_expression_opt RB {$$=setTypeElementType($1, setTypeExpr(makeType(T_ARRAY), $3));}
    |LP parameter_type_list_opt RP {$$=setTypeExpr(makeType(T_FUNC), $2);}
    |direct_abstract_declarator LP parameter_type_list_opt RP {$$=setTypeElementType($1, setTypeExpr(makeType(T_FUNC), $3));}
    ;

statement_list_opt:
                                {$$=makeNode(N_STMT_LIST_NIL, NIL, NIL, NIL);}
    |statement_list             {$$=$1;}
    ;

statement_list:
    statement                   {$$=makeNode(N_STMT_LIST_NIL, $1, NIL, makeNode(N_STMT_LIST_NIL,  NIL, NIL, NIL));}
    |statement_list statement   {$$=makeNodeList(N_STMT_LIST, $1, $2);}
    ;

statement:
    labeled_statement           {$$=$1;}
    |compound_statement         {$$=$1;}
    |expression_statement       {$$=$1;}
    |selection_statement        {$$=$1;}
    |iteration_statement        {$$=$1;}
    |jump_statement             {$$=$1;}
    ;

labeled_statement:
    CASE_SYM constant_expression COLON statement    {$$=makeNode(N_STMT_LABEL_CASE, $2, NIL, $4);}
    |DEFAULT_SYM COLON statement                    {$$=makeNode(N_STMT_LABEL_DEFAULT, NIL, $3, NIL);}
    ;

compound_statement:
    LR {$$=current_id; current_level++;} declaration_list_opt statement_list_opt RR {checkForwardReference(); $$=makeNode(N_STMT_COMPOUND, $3, NIL, $4); current_id=$2; current_level--;}
    ;

expression_statement:
    SEMICOLON                   {$$=makeNode(N_STMT_EMPTY, NIL, NIL, NIL);}
    |expression SEMICOLON       {$$=makeNode(N_STMT_EXPRESSION, NIL, $1,NIL);}
    ;

selection_statement:
    IF_SYM LP expression RP statement
    |IF_SYM LP expression RP statement ELSE_SYM statement
    |SWITCH_SYM LP expression RP statement
    ;

iteration_statement:
    WHILE_SYM LP expression RP statement
    |DO_SYM statement WHILE_SYM LP expression RP SEMICOLON
    |FOR_SYM LP for_expression RP statement
    ;

for_expression:
    expression_opt SEMICOLON expression_opt SEMICOLON expression_opt
    ;

expression_opt:
    
    |expression
    ;

jump_statement:
    RETURN_SYM expression SEMICOLON
    |CONTINUE_SYM SEMICOLON
    |BREAK_SYM SEMICOLON
    ;

arg_expression_list_opt:
    
    |arg_expression_list
    ;

arg_expression_list:
    assignment_expression
    |arg_expression_list COMMA assignment_expression
    ;

constant_expression_opt:
    
    |constant_expression
    ;

constant_expression:
    expression
    ;

expression:
    comma_expression
    ;

comma_expression:
    assignment_expression
    ;

assignment_expression:
    conditional_expression
    |unary_expression ASSIGN assignment_expression
    ;

conditional_expression:
    logical_or_expression
    ;

logical_or_expression:
    logical_and_expression
    |logical_or_expression BARBAR logical_and_expression
    ;

logical_and_expression:
    bitwise_or_expression
    |logical_and_expression AMPAMP bitwise_or_expression
    ;

bitwise_or_expression:
    bitwise_xor_expression
    ;

bitwise_xor_expression:
    bitwise_and_expression
    ;

bitwise_and_expression:
    equality_expression
    ;

equality_expression:
    relational_expression
    |equality_expression EQL relational_expression
    |equality_expression NEQ relational_expression
    ;

relational_expression:
    shift_expression
    |relational_expression LSS shift_expression
    |relational_expression GTR shift_expression
    |relational_expression LEQ shift_expression
    |relational_expression GEQ shift_expression
    ;

shift_expression:
    additive_expression
    ;

additive_expression:
    multiplicative_expression
    |additive_expression PLUS multiplicative_expression
    |additive_expression MINUS multiplicative_expression
    ;

multiplicative_expression:
    cast_expression
    |multiplicative_expression STAR cast_expression
    |multiplicative_expression SLASH cast_expression
    |multiplicative_expression PERCENT cast_expression
    ;

cast_expression:
    unary_expression
    |LP type_name RP cast_expression
    ;

unary_expression:
    postfix_expression
    |PLUSPLUS unary_expression
    |MINUSMINUS unary_expression
    |AMP cast_expression
    |STAR cast_expression
    |EXCL cast_expression
    |MINUS cast_expression
    |PLUS cast_expression
    |SIZEOF_SYM unary_expression
    |SIZEOF_SYM LP type_name RP
    ;

postfix_expression:
    primary_expression
    |postfix_expression LB expression RB
    |postfix_expression LP arg_expression_list_opt RP
    |postfix_expression PERIOD IDENTIFIER
    |postfix_expression ARROW IDENTIFIER
    |postfix_expression PLUSPLUS
    |postfix_expression MINUSMINUS
    ;

primary_expression:
    IDENTIFIER
    |INTEGER_CONSTANT
    |FLOAT_CONSTANT
    |CHARACTER_CONSTANT
    |STRING_LITERAL
    |LP expression RP
    ;

type_name:
    declaration_specifiers abstract_declarator_opt
    ;

%%
int yyerror(char *s){
    printf("Error : %s \n", s);
    exit(1);
}

void main()
{
    yyparse();
    printf("Done\n");
}