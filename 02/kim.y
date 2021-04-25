%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
int yylval;
char ch;
%}
%start S
%token PLUS STAR LP RP number 

%%
S	: E			{printf("%d", $1);}
	;
E	: E PLUS T	{$$ = $1 + $3;}
	| T			{$$ = $1;}
	;
T	: T STAR F	{$$ = $1 * $3;}
	| F			{$$ = $1;}
	;
F	: LP E RP	{$$ = $2;}
	| number	{$$ = $1;}
	;
%%

void yyerror(){
	printf("Error!\n");
	return ;
}

int yylex(){
	while (ch==' '||ch=='\t'){
		ch = getchar();
	}
	if ('0' <= ch && ch <= '9'){
		int i = 0;
		char * yytext = (char)malloc(100);
		do {
			yytext[i++] = ch;
			ch = getchar();
		} while ('0' <= ch && ch <= '9');

	} else if (ch == '+') {
		ch = getchar();
		return PLUS;
	} else if (ch == '*') {
		ch = getchar();
		return STAR;
	} else if (ch == '(') {
		ch = getchar();
		return LP;
	} else if (ch == ')') {
		ch = getchar();
		return RP;
	} else {
		yyerror();
	}
}
void main(){
	ch = getchar();
	yyparse();
}
