#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt�� �� �� �����ϴ�." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int numCases = 0; numCases < cases; numCases++) {
		int num;
		instream >> num;
		int *ary = new int[num];
		for (int sNum = 0; sNum < num; sNum++)
			instream >> ary[sNum]; // ó�� ���� ary�� �ִ´�
		bool check = false;
		for (int i = 0; i < 1000; i++) { // �ִ� õ������ �ݺ�
			for (int k = 0; k < num; k++) {
				if (ary[k] != 0) // 0�� �ƴ϶�� ZERO���� ���̻� Ȯ���� �ʿ� �����Ƿ� break
					break;
				else {
					if (k == num - 1) // ������ �����ߴµ� ��� 0�̶��
						check = true; // check�� true�� (ZERO)
				}
			}
			if (check == false) {
				int store = ary[0];
				for (int j = 0; j < num; j++) {
					if (j != num - 1) // j�� ������ �ƴ϶��
						ary[j] = abs(ary[j] - ary[j + 1]);
					else // j�� �����̶��
						ary[j] = abs(ary[j] - store);
				}
			}
			else { // check�� true�̸�
				cout << "ZERO" << endl;
				break;
			}
		}
		if (check == false)
			cout << "LOOP" << endl;
	}
	return 0;
}