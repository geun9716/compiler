#include <stdio.h>
#include <stdlib.h>
enum{
	NUMBER,	
	PLUS,	
	MINUS,
	STAR,	
	SLASH,
	LPAREN,	
	RPAREN,
	END,
	Null
} token;
int num;
char ch = ' ';
char * tmp;
void expression();

void error(int err){
	printf("Error : ");
	switch(err){
		case 1 :
			printf("잘못된 수식입니다.\n");
			break;
		case 2 : 
			printf("괄호안 수식이 정상적으로 종료되지 않았습니다.\n");
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
void get_token(){
	//blank trim
	while(ch==' '){
		ch = getchar();
	}
	//NUMBER
	if ('0' <= ch && ch <= '9'){
		token = NUMBER;
		tmp = (char *)calloc(100, sizeof(char));
		int cnt = 0;
		while(('0' <= ch && ch <= '9')){
			tmp[cnt++] = ch;
			ch = getchar();
		}
		num = atoi(tmp);
		//printf("num : %d\n", num);
		free(tmp);
	}else if (ch == '+'){
		token = PLUS;
		ch = getchar();
	} else if (ch == '-'){
		token = MINUS;
		ch = getchar();
	} else if (ch == '*'){
		token = STAR;
		ch = getchar();
	} else if (ch == '/'){
		token = SLASH;
		ch = getchar();
	} else if (ch == '('){
		token = LPAREN;
		ch = getchar();
	} else if (ch == ')'){
		token = RPAREN;
		ch = getchar();
	} else if (ch == '\n'){
		token = END;
	} else {
		token = Null;
		error(4);
	}
}
void factor(){
	if(token == NUMBER){
		get_token();
	} else if (token == LPAREN){
		get_token();
		expression();
		if(token == RPAREN)
			get_token();
		else{
			error(2);	
		}
	} else
		error(1);
}
void term(){
	factor();
	while(token==STAR || token == SLASH){
		get_token();
		factor();
	}
}
void expression(){
	term();
	while(token==PLUS || token == MINUS){
		get_token();
		term();
	}
}
int main(void){
	ch = getchar();
	get_token();
	expression();
	if (token!=END){
		error(3);
	}
	printf("Expression is sentence\n");
	return 0;
}
