/*
   hw2  
*/
%{
#include <stdio.h>
#include <stdlib.h>

enum tnumber {
   TEOF, TNUMBER, TPLUS, TMINUS, TTIMES,
   TCOMMA, TSEMICOLON, TCOLON, TASSIGN, TDOT, TDDOT,
   TLPAREN, TRPAREN, TLBRACKET, TRBRACKET, TEQUAL, TNEQUAL,
   TLESS, TLESSE, TGREAT, TGREATE, TBEGIN, TEND,
   TDIV, TDIV2,
   ARRAYSYM, CONSTSYM, DOSYM, BREAKSYM,
   IFSYM, INTSYM, CHARSYM, FLOATSYM, DOUBLESYM, SWITCHSYM, CASESYM,
   WHILESYM, TERROR, CLASS, CLASSNAME, VAR, COMMENTSTART, COMMENT, BLANK,
   VOID, FUNCTIONNAME, PUBLIC, PROTECTED, POINTERVAL, NEXT, NEW, RETURN, PRIVATE
};

int LineNumber = 0;

#undef yywrap
%}
letter   [a-zA-Z_]
digit   [0-9]
%%
"+"   return(TPLUS);
"-"   return(TMINUS);
"*"   return(TTIMES);
"/"   return(TDIV);
"%"   return(TDIV2);
","   return(TCOMMA);
";"   return(TSEMICOLON);
":"   return(TCOLON);
"("   return(TLPAREN);
")"   return(TRPAREN);
"["   return(TLBRACKET);
"]"   return(TRBRACKET);
"="   return(TASSIGN);
"=="   return(TEQUAL);
"!="   return(TNEQUAL);
"<"   return(TLESS);
"<="   return(TLESSE);
">"   return(TGREAT);
">="   return(TGREATE);
\.   return(TDOT);

"{"   return(TBEGIN);
"}"   return(TEND);
float   return(FLOATSYM);
do   return(DOSYM);
if   return(IFSYM);
while   return(WHILESYM);
int   return(INTSYM);
char   return(CHARSYM);
const   return(CONSTSYM);
double   return(DOUBLESYM);
switch   return(SWITCHSYM);
case   return(CASESYM);
break  return(BREAKSYM);
(class|Class)   return(CLASS);
(Account|List|Cell|cell|Stack)   return(CLASSNAME);
(account_number|account|balance|initial|amount|x|elements|c|top)   return(VAR);
"//"   return(COMMENTSTART);
("constructor Account"|"method deposit"|"class Account")      return(COMMENT);
void   return(VOID);
(deposit|empty|add|push|get|Queue|pop|push|put)      return(FUNCTIONNAME);
" "   return(BLANK);
public		return(PUBLIC);
protected	return(PROTECTED);
private		return(PRIVATE);
("*rear"|rear)	return(POINTERVAL);
next		return(NEXT);
new		return(NEW);
return		return(RETURN);
{digit}+   return(TNUMBER);
[ \t\r]   ;
\n   LineNumber++;
.   return(TERROR);
%%
main()
{
   enum tnumber tn;

   printf("Start of Hw2 C\n");
   while ((tn = yylex()) != TEOF) {
      switch (tn) {
      case TNUMBER:
         printf("\t(%2i, %s)\n", tn, yytext); break;
      case TERROR:
         printf("ERROR -- line %d : [%c]\n", LineNumber, yytext[0]); break;
      case BLANK:
   break;
      default:
         //printf("\t(%2i, 0)\n", tn);
   printf("\t(%2i, %s)\n", tn, yytext); break;

      }
   }
}

yywrap() { printf("End of Hw2 C\n"); return 1; }