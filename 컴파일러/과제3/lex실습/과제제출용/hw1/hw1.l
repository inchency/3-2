/*
   hw1
*/
%{
#include <stdio.h>
#include <stdlib.h>

enum tnumber {
	ERROR, INT, REAL, PLUS, MINUS, MUL, DIV, REM, EXP, LPAREN, RPAREN,
	SQRT, SIN, COS, ABS, VAR, BLANK
};

#undef yywrap
%}

digit   [0-9]

%%
"+"   return(PLUS);
"-"   return(MINUS);
"*"   return(MUL);
"/"   return(DIV);
"%"   return(REM);
"^"   return(EXP);
"("   return(LPAREN);
")"   return(RPAREN);
"sqrt"   return(SQRT);
"sin"   return(SIN);
"cos"   return(COS);
"abs"   return(ABS);
"x"	return(VAR);
"y"	return(VAR);
"var1"	return(VAR);
"var2"	return(VAR);
{digit}+   return(INT);
{digit}+\.{digit}+	return(REAL);
" "	return(BLANK);
.	return(ERROR);

%%
main()
{
   enum tnumber tn;
   printf("Start of Hw1\n");
   while ((tn = yylex()) != ERROR) {
      switch (tn) {
      case INT:
         printf("\t(%2i, %s)\n", tn, yytext); break;
      case REAL:
         printf("\t(%2i, %s)\n", tn, yytext); break;
      case VAR:
         printf("\t(%2i, %s)\n", tn, yytext); break;
      case BLANK:
	break;
      default:
         printf("\t(%2i, 0)\n", tn);
      }
   }
  printf("\t(0, 0)\n");
}