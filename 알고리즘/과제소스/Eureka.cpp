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
	instream >> cases;
	for (int testCases = 0; testCases < cases; testCases++) {
		int num;
		instream >> num;
		int n = 1;
		int result = 0;
		//n(n+1)/2 <= num �̿����� n�� ���غ���
		while (1) {
			if (result <= num) {
				result = n*(n + 1) / 2;
				n++;
			}
			else {
				n -= 2; // ���� ������ 2�� ����� ���� ���ϴ� ���� ����
				break;
			}
		}
		int *ary = new int[n];
		for (int i = 0; i < n; i++)
			ary[i] = NULL; // �ʱ�ȭ
		for (int i = 1; i <= n; i++)
			ary[i - 1] = i * (i + 1) / 2;
		int sum = 0;
		int check = false;
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				for (int k = j; k < n; k++) {
					sum = ary[i] + ary[j] + ary[k];
					if (sum == num) { // 3���� ���� ���� num�� ���� ���� ������
						check = true; // check true �� ������ش�
						break;
					}
				}
			}
		}
		if (check)
			cout << "1" << endl;
		else // 3���� ���� ���� ���� ���
			cout << "0" << endl;
		delete ary;
	}
	return 0;
}