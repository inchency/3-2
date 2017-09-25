#include <iostream>
#include <fstream>
using namespace std;

int binomicalCoefficient(int a, int b);
int gcd(int a, int b); // 최대공약수 구하는 함수

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt를 열 수 없습니다." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int testCases = 0; testCases < cases; testCases++) {
		int N, K;
		instream >> N >> K;
		cout << binomicalCoefficient(N, K) << endl;
	}
	return 0;
}

int binomicalCoefficient(int a, int b) {
	if (a == b || b == 0) // 같을 경우는 이항계수가 1임 혹은 b가 0일때도 1임
		return 1;
	else if (a / 2 < b)  // ex)20 Combination 17일 경우 -> 20 Combination 3으로 변환
		b = a - b;
	int *aryA = new int[b]; // 각 곱해야 해야할 배열을 동적할당해서 생성(분자)
	int *aryB = new int[b]; // 각 곱해야 해야할 배열을 동적할당해서 생성(분모)
							// a가 만약 20이라면 20,19,18 .... 2,1 이런식으로 저장할거임 단 b의 숫자 갯수만큼만
	int tempA = a;
	int tempB = b;
	for (int i = 0; i < b; i++, tempA--, tempB--) {
		aryA[i] = tempA;
		aryB[i] = tempB;
	}
	// 여기까지 배열에 각각 숫자를 넣어줬고 이제 분모에 있는 숫자들을 약분할수있으면 약분해야한다.
	int gcdAB; // 두수의 최대공약수
	for (int i = 0; i < b; i++) { // 분모도는 for문
		for (int j = 0; j < b; j++) { // 분자도는 for문
			gcdAB = gcd(aryA[j], aryB[i]);
			aryA[j] /= gcdAB;
			aryB[i] /= gcdAB;
			if (aryB[i] == 1) // 1이 되면 더이상 for문을 돌 필요가 없음
				break;
		}
	}
	// 여기까지 분모는 다 1로 제거되었고 분자만 남아있음 전부 계산하기엔 수가 너무 커지면 에러가 나므로 한번 곱하고 남은 나머지를 다음걸로 곱하는 식으로 반복
	int result = aryA[0];
	for (int i = 1; i < b; i++)
		result = result * aryA[i] % 10007;
	return result;
}

int gcd(int a, int b) {
	if (b == 0)
		return a;
	else
		return gcd(b, a%b);
}