example : lex.yy.c y.tab.c
	cc lex.yy.c y.tab.c

lex.yy.c : kim.l
	lex kim.l
y.tab.c : kim.y
	yacc -d kim.y

clear : 
	rm lex.yy.c y.tab.c y.tab.h
	clear