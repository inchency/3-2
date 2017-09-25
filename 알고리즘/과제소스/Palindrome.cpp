#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream instream("input.txt");

	if (!instream.is_open()) {
		cout << "input.txt�� �� �� �����ϴ�." << endl;
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
			// ������� j������ ��ȯ�Ϸ� (�迭�����δ� ������ �ݴ����� palindrome�� ���ϴ� ���̱� ������ ��� ����
			if ((z + 1) % 2 == 0) { // ������ �ڸ����� ¦���̸� (���⼭ z+1�� ������ �ڸ��� �迭�� 0���� �����ϴϱ�)
				for (int p = 0, k = z; p < (z + 1) / 2; p++, k--) {
					if (remain[p] != remain[k]) {
						//check = 0;
						break;
					}
					else {
						if (p == z / 2) // ���������� �����ߴµ� ��Ī���� �ʴ°��� ������ check=1�� ���ش�
							check = 1;
					}
				}
			}
			else { // ������ �ڸ����� Ȧ���̸�
				for (int p = 0, k = z; p < z / 2; p++, k--) {
					if (remain[p] != remain[k]) {
						//check = 0;
						break;
					}
					else {
						if (p == z / 2 - 1) // ���������� �����ߴµ� ��Ī���� �ʴ°��� ������ check=1�� ���ش�
							check = 1;
					}
				}
			}
			num = originNum;
			if (check == 1) // j�������� �̹� palindrome ������ ���̻� ���� ������ ���� �ʿ䰡 ������ break
				break;
		}
		cout << check << endl;
	}
	return 0;
}