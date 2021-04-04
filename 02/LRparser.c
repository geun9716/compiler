#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMBER 256
#define PLUS 257
#define STAR 258
#define LP 259
#define RP 260
#define END 261
#define EXPRESSION 0
#define TERM 1
#define FACTOR 2
#define ACC 999

int action[12][6]={
	{5, 0, 0, 4, 0, 0},
	{0, 6, 0, 0, 0, ACC},
	{0, -2, 7, 0, -2, -2},
	{0, -4, -4, 0, -4, -4},
	{5, 0, 0, 4, 0, 0},
	{0, -6, -6, 0, -6, -6},
	{5, 0, 0, 4, 0, 0},
	{5, 0, 0, 4, 0, 0},
	{0, 6, 0, 0, 11, 0},
	{0, -1, 7, 0, -1, -1},
	{0, -3, -3, 0, -3, -3},
	{0, -5, -5, 0, -5, -5}
};
int go_to[12][3] = {
	{1,2,3},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{8, 2, 3},
	{0, 0, 0},
	{0, 9, 3},
	{0, 0, 10},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};

int prod_left[7] = {0, EXPRESSION, EXPRESSION, TERM, TERM, FACTOR, FACTOR};
int prod_length[7] = {0, 3, 1, 3, 1, 3, 1};

int stack[1000];
double value[1000];
char yytext[32];

int top = -1;
int sym;
double yylval;
int isFloat = 0;
static char ch = ' ';
void printval(){
	printf("stack { ");
	for(int i = 0 ; i <= top; i++){
		printf("%2d ", stack[i]);
	}
	printf("}\n");

	printf("value { ");
	for(int i = 0 ; i <= top; i++){
		printf("%2.2f ", value[i]);
	}
	printf("}\n");
}

void yyerror(int err){
	printf("Error : ");
	switch(err){
		case 1 :
			printf("잘못된 수식입니다.\n");
			break;
		case 2 : 
			printf("액션테이블에 존재하지 않는 상태코드입니다.\n");
			break;
		case 3 : 
			printf("프로그램이 정상적으로 종료하지 않았습니다.\n");
			break;
		case 4 : 
			printf("잘못된 입력입니다.\n");
			break;
		default : 
			printf("원인을 알 수 없는 에러 입니다.");
			break;
	}
	exit(1);
}
int yylex(){
	int i=0;
	while (ch==' '||ch=='\t'){
		ch = getchar();
	}
	if('0' <= ch && ch <= '9'){
		do {
			yytext[i++] = ch;
			if(ch == '.')
				isFloat = 1;
			ch = getchar();
		}while ('0' <= ch && ch <= '9'|| ch == '.');
		yytext[i] = '\0';
		yylval = atof(yytext);
		return NUMBER;
	} else if (ch == '+'){
		ch = getchar();
		return PLUS;
	} else if (ch == '*'){
		ch = getchar();
		return STAR;
	} else if (ch == '('){
		ch = getchar();
		return LP;
	} else if (ch == ')'){
		ch = getchar();
		return RP;
	} else if (ch == '\n'){
		return END;
	} else
		yyerror(4);
}

void push(int i){
	stack[++top] = i;
}
void shift(int i){
	push(i);
	value[top] = yylval;
	sym = yylex();
}
void reduce(int i){
	int old_top;
	top -= prod_length[i];
	old_top = top;
	push(go_to[stack[old_top]][prod_left[i]]);
	
	switch(i){
		case 1 : 
			value[top] = value[old_top+1]+value[old_top+3];
			break;
		case 2 : 
			value[top] = value[old_top+1];
			break;
		case 3 :
			value[top] = value[old_top+1]*value[old_top+3];
			break;
		case 4 : 
			value[top] = value[old_top+1];
			break;
		case 5 : 
			value[top] = value[old_top+2];
			break;
		case 6 : 
			value[top] = value[old_top+1];
			break;
		default : 
			yyerror(1);
			break;
	}
	//printval();
} 

int yyparse(){
	int i;
	stack[++top] = 0;
	sym = yylex();
	do {
		i = action[stack[top]][sym-256];
		if( i == ACC){
			if(isFloat){
				printf("value : %lf\n", value[top]);
			} else {
				printf("value : %d\n", (int) value[top]);
			}
			printf("success!\n");
		}else if (i>0) 
			shift(i);
		else if (i < 0) 
			reduce(-i);
		else
			yyerror(2);
	} while (i != ACC);
}


int main(){
	yyparse();
	return 0;
}


