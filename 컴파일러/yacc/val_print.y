%{
	#include <stdio.h>
%}
%token NUMBER STRING
%%
print: print word
	| word
	;
word:	NUMBER {printf("number : %d\n", yylval);}
 	| STRING {printf("string : %s\n", yylval);}
	;
%%
yylex()
{
	char ch;

	while ((ch=getchar())==' ' || ch=='\t')
		; 	//skip
	if (ch == '\n')
		return 0;
	else if (isdigit(ch)) {
		ungetc(ch, stdin);
		fscanf(stdin, "%d", &yylval);
		return NUMBER;
	} else if (isalpha(ch)) {
		ungetc(ch, stdin);
		fscanf(stdin, "%s", yylval);
		return STRING;
	}
}
