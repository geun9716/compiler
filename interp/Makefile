all : lex.yy.c y.tab.c
	gcc -g -w -o interp lex.yy.c y.tab.c interp.c lib.c

lex.yy.c : interp.l
	lex interp.l
y.tab.c : interp.y
	yacc -d interp.y

clear : 
	rm lex.yy.c y.tab.c y.tab.h
	clear