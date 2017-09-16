/*
	LRS(Language Recognition System)

	테스트 스트링 : "abb$", "aaabbb$"

<실습> main()의 getchar() 대신에 전체 스트링을 한꺼번에 문자배열에 입력하여
	처리하는 방식으로 이 프로그램을 수정하시오.
<실습> 유사한 다른 문법에 대한 언어인식 프로그램을 작성해 보시오.
*/
/*
	Language Recognizer for the following CFG.

	G = ({S, A}, {a, b}, P, S)
		P: S --> aAb
		   A --> aS
		   A --> b
*/

#include <stdio.h>

char ch;
int errflag = 0;

/*
	Recognition-failed message.
*/
void error()
{
	if (!errflag) {
		puts("FAIL");
		errflag = 1;
	}
}

void pa()
{
	if (ch == 'a')
		ch = getchar();
	else error();
}

void pb()
{
	if (ch == 'b')
		ch = getchar();
	else error();
}

/*
	S --> aAb
*/
void pS()
{
	void pA();

	if (ch == 'a') {
		pa(); pA(); pb();
	} else error();
}

/*
	A --> aS
	A --> b
*/
void pA()
{
	switch (ch) {
	case 'a':
		pa(); pS();
		break;
	case 'b':
		pb();
		break;
	default:
		error();
	}
}

void main()
{
	puts("Production Rules:");
	puts("\tS --> aAb");
	puts("\tA --> aS");
	puts("\tA --> b");
	printf("$로 끝나는 입력스트링 : ");

	ch = getchar();
	pS();

	if (!errflag && (ch == '$' || ch == '\n')) puts("OK");
	else error();
}
