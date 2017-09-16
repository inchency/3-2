%{
/*
	JSON file lexical analysis
*/
	#include <stdio.h>
	#include "y.tab.h"

//	int yylineno=1;
%}

%option yylineno

letter	[a-zA-Z]
digit	[0-9]
digit19	[1-9]

%%
"{"	return(LBRACE);
"}"	return(RBRACE);
"["	return(LBRACKET);
"]"	return(RBRACKET);
":"	return(COLON);
","	return(COMMA);
true	return(TRUE);
flase	return(FALSE);
null	return(TNULL);

'0'	{ yylval.i = 0; return(INT); }
{digit19}{digit}*	{ yylval.i = atoi(yytext); return(INT); }
{digit}?\.{digit}*	{ yylval.d = atof(yytext); return(DOUBLE); }
#"\""{letter}({letter}|{digit})*"\""	{ strcpy(yylval.str, yytext); return(STRING); }	// 따옴표 안에 문장부호, 공백문자 허용 안함!
#\".*\"	return(STRING);	// "abc":"def" 를 1개의 string으로 인식하는 오류 발생!
\"[^\"]*\"	{ strcpy(yylval.str, yytext); return(STRING); }

[ \t\r]	;
\n	{ yylineno++; }
.	return 0;
%%
