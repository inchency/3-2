%{
	#include <stdio.h>
%}
%token NUMBER
%%
assign_stmt: expression {printf("= %d\n", $1);}
	;
expression: expression '+' NUMBER {$$ = $1 + $3;}
	| NUMBER {$$ = $1;}
	;
%%
yylex()
{
	int ch;

	while ((ch=getchar())==' ' || ch=='\t')
		;	//skip
	if (ch=='\n') return 0;
	if (isdigit(ch)) {
		ungetc(ch, stdin);
		fscanf(stdin, "%d", &yylval);
		return NUMBER;
	}
	return ch;
}
