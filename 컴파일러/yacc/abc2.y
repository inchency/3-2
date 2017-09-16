%{
	#include <stdio.h>
%}
%%
start: a { puts("\tCFG: start -> a"); \
	 printf("Parsing - GOOD!!!"); };
a: 	'a'b 	{ puts("\tCFG: a -> ta b"); }
	| 'A'b 	{ puts("\tCFG: a -> tA b"); }
	;
b: 	'b'c 	{ puts("\tCFG: b -> tb c"); }
	| 'B'c 	{ puts("\tCFG: b -> tB c"); }
	;
c: 	'c' 	{ puts("\tCFG: c -> tc"); }
	| 'C' 	{ puts("\tCFG: c -> tC"); }
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
