%{
	#include <stdio.h>
%}
%%
start: a { printf("sequential \"ABC\""); };
a: 	'a'b 
	| 'A'b 
	;
b: 	'b'c 
	| 'B'c 
	;
c: 	'c' 
	| 'C' 
	;
%%
yylex() {
	char ch;

	ch = getchar();
	if (isalpha(ch)) return ch;
}

main() {
	yyparse();
}
