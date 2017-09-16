all :
	yacc -d yac.y
	flex lex.l
	gcc -o json y.tab.c lex.yy.c -ly -lfl
