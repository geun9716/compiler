example : lex.yy.c y.tab.c
	gcc -g -w -o com lex.yy.c y.tab.c print.c supportfunc.c main.c semantic.c code_generator.c sem_print.c

lex.yy.c : kim.l
	lex kim.l
y.tab.c : kim.y
	yacc -d kim.y

clear : 
	rm lex.yy.c y.tab.c y.tab.h
	clear