#include <iostream>
#include <fstream>

using namespace std;

int gcd(int a, int b); // 최대공약수 함수 (알고리즘 시간에 배운 recursive 이용)
int lcm(int a, int b); // 최소공배수 함수

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt를 열 수 없습니다." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int numCases = 0; numCases < cases; numCases++) {
		int a, b; // a는 분자 b는 분모
		instream >> a >> b;

		int i = 2;
		while (1) {
			int testA = a % gcd(a, b);
			int testB = b % gcd(a, b);
			int store_gcd = gcd(a, b);
			if (testA == 0 && testB == 0) { // 기약분수가 아니라면 기약분수로 먼저 만들어준다
				a = a / store_gcd;
				b = b / store_gcd;
			}
			if (a == 1) {
				cout << b << endl;
				break;
			}
			else {
				int l = lcm(b, i); // l은 b,i의 최소공배수
				int la = l / i; // la는 i의 분자
				int oa = l / b * a; // oa는 원래수의 분자
				if (la <= oa) { // la가 더 작은경우는 단위 분수가 가능하다는 뜻
					a = oa - la;
					b = l;
				}
				i++;
			}
		}
	}
	return 0;
}

int gcd(int a, int b) { // 알고리즘 시간에 배운 재귀적(recursive)를 이용하였다.
	if (b == 0)
		return a;
	else
		return gcd(b, a%b);
}
int lcm(int a, int b) {
	int c = gcd(a, b); // c는 a와b의 최대공약수
	return c*(a / c)*(b / c);
}