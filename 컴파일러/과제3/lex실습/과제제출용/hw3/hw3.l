/*
   hw3
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
    INTSYM, CHARSYM, FLOATSYM, DOUBLESYM, SWITCHSYM, CASESYM,
   WHILESYM, TERROR, CLASS, CLASSNAME, VAR, COMMENTSTART, COMMENT, BLANK,
    FUNCTIONNAME, RETURN, REAL, FUNCTIONDEF, IF, ELIF, ELSE, IN, SMALLDOWNPYO, TRY, IMPORT, LIBRARY, EXCEPT, LEN, RANGE, BIGDOWNPYO, FOR, AND, PRINT, SEQUENCE
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
while   return(WHILESYM);
int   return(INTSYM);
char   return(CHARSYM);
const   return(CONSTSYM);
double   return(DOUBLESYM);
switch   return(SWITCHSYM);
case   return(CASESYM);
break  return(BREAKSYM);
(class|Class)   return(CLASS);
	return(CLASSNAME);
(number|sign_mark|tmp|num|decimal|head_num|result|pos|theNumber|likeFile|text|fp|fileLines|word|line)	return(VAR);
"#"   return(COMMENTSTART);
(commanumber.py|factorial.py|fileword3.py)      return(COMMENT);
import		return(IMPORT);
(string|cStringIO)		return(LIBRARY);
(comma_number|split|factorial|StringIO|word_list|readlines)	return(FUNCTIONNAME);
def	return(FUNCTIONDEF);
if	return(IF);
elif	return(ELIF);
else	return(ELSE);
in	return(IN);
range	return(RANGE);
\'	return(SMALLDOWNPYO);
\"	return(BIGDOWNPYO);
try	return(TRY);
except		return(EXCEPT);
len		return(LEN);
for		return(FOR);
and		return(AND);
print		return(PRINT);
{digit}L	return(SEQUENCE);
" "   return(BLANK);
return		return(RETURN);




{digit}+\.{digit}+	return(REAL);
{digit}+   return(TNUMBER);

[ \t\r]   ;
\n   LineNumber++;
.   return(TERROR);
%%
main()
{
   enum tnumber tn;

   printf("Start of Hw3 python C\n");
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

yywrap() { printf("End of Hw3 python\n"); return 1; }
