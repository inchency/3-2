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
	int remain[20] = { 0 };
	instream >> cases;
	for (int i = 0; i < cases; i++) {
		int num;
		int originNum;
		instream >> num;
		originNum = num;
		int check = 0;
		for (int j = 2; j <= 64; j++) {
			int z = 0;
			while (num >= j) {
				remain[z] = num % j;
				num /= j;
				z++;
			}
			remain[z] = num;
			// 여기까지 j진수로 변환완료 (배열상으로는 순서가 반대지만 palindrome을 비교하는 것이기 때문에 상관 없음
			if ((z + 1) % 2 == 0) { // 진수의 자리수가 짝수이면 (여기서 z+1은 진수의 자리수 배열은 0부터 시작하니까)
				for (int p = 0, k = z; p < (z + 1) / 2; p++, k--) {
					if (remain[p] != remain[k]) {
						//check = 0;
						break;
					}
					else {
						if (p == z / 2) // 마지막까지 도달했는데 대칭되지 않는것이 없으면 check=1로 해준다
							check = 1;
					}
				}
			}
			else { // 진수의 자리수가 홀수이면
				for (int p = 0, k = z; p < z / 2; p++, k--) {
					if (remain[p] != remain[k]) {
						//check = 0;
						break;
					}
					else {
						if (p == z / 2 - 1) // 마지막까지 도달했는데 대칭되지 않는것이 없으면 check=1로 해준다
							check = 1;
					}
				}
			}
			num = originNum;
			if (check == 1) // j진수에서 이미 palindrome 했으니 더이상 다음 진수를 비교할 필요가 없으니 break
				break;
		}
		cout << check << endl;
	}
	return 0;
}