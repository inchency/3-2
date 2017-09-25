#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt를 열 수 없습니다." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int testCases = 0; testCases < cases; testCases++) {
		int num;
		instream >> num;
		int n = 1;
		int result = 0;
		//n(n+1)/2 <= num 이여야함 n을 구해보면
		while (1) {
			if (result <= num) {
				result = n*(n + 1) / 2;
				n++;
			}
			else {
				n -= 2; // 원래 값에서 2를 빼줘야 내가 원하는 값이 나옴
				break;
			}
		}
		int *ary = new int[n];
		for (int i = 0; i < n; i++)
			ary[i] = NULL; // 초기화
		for (int i = 1; i <= n; i++)
			ary[i - 1] = i * (i + 1) / 2;
		int sum = 0;
		int check = false;
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				for (int k = j; k < n; k++) {
					sum = ary[i] + ary[j] + ary[k];
					if (sum == num) { // 3개를 더한 값이 num과 같은 값이 있으면
						check = true; // check true 로 만들어준다
						break;
					}
				}
			}
		}
		if (check)
			cout << "1" << endl;
		else // 3개를 더한 값이 없는 경우
			cout << "0" << endl;
		delete ary;
	}
	return 0;
}