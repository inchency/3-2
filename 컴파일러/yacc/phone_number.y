%{
	/* phone_numbers: ex) 02-123-1234 */
	#include <stdio.h>
%}
%token NUMBER HYPHEN
%%
phone_number: number HYPHEN number HYPHEN number { printf("phone number"); }
	;
number : number NUMBER
	| NUMBER
	;
%%
yylex()
{
	int ch;

	ch = getchar();
	if (ch == '\n') 
		return 0;
	else if (isdigit(ch))
		return NUMBER;
	else if (ch == '-')
		return HYPHEN;
}

main() {
	yyparse();
}
