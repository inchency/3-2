#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt를 열 수 없습니다." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int numCases = 0; numCases < cases; numCases++) {
		int num;
		instream >> num;
		int *ary = new int[num];
		for (int sNum = 0; sNum < num; sNum++)
			instream >> ary[sNum]; // 처음 수를 ary에 넣는다
		bool check = false;
		for (int i = 0; i < 1000; i++) { // 최대 천번까지 반복
			for (int k = 0; k < num; k++) {
				if (ary[k] != 0) // 0이 아니라면 ZERO인지 더이상 확인할 필요 없으므로 break
					break;
				else {
					if (k == num - 1) // 끝까지 도달했는데 계속 0이라면
						check = true; // check를 true로 (ZERO)
				}
			}
			if (check == false) {
				int store = ary[0];
				for (int j = 0; j < num; j++) {
					if (j != num - 1) // j가 끝값이 아니라면
						ary[j] = abs(ary[j] - ary[j + 1]);
					else // j가 끝값이라면
						ary[j] = abs(ary[j] - store);
				}
			}
			else { // check가 true이면
				cout << "ZERO" << endl;
				break;
			}
		}
		if (check == false)
			cout << "LOOP" << endl;
	}
	return 0;
}