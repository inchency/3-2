#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

bool decAry(int a, int b);

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
		int *ary = new int[num];
		for (int i = 0; i < num; i++)
			instream >> ary[i];
		sort(ary, ary + num, decAry);
		/*for (int i = 0; i < num; i++)
		cout << ary[i] << " ";
		cout << endl;*/
		int QIndex, bigCnt = 0, smallCnt = 0, flag = false, flag2 = false; // ť�ε���, �ε����̻��ΰ� ī��Ʈ, �ε��� �����ΰ� ī��Ʈ, �ε��� �̻��ΰ� ��ã���� flag = false�ϰ� small�ΰ� üũ����, flag2�� QIndex�� ������
		for (int i = 0; i <= num; i++) {
			QIndex = i;
			bigCnt = 0, smallCnt = 0;
			flag = false;
			for (int j = 0; j < num; j++) {
				if (bigCnt == QIndex && !flag)
					flag = true;
				if (ary[j] >= QIndex && !flag) {
					bigCnt++;
				}
				if (flag && ary[j] <= QIndex) {
					smallCnt++;
				}
			}
			if (bigCnt == QIndex && num - QIndex == smallCnt) {
				cout << QIndex << endl;
				flag2 = true;
			}
		}
		if (!flag2)
			cout << "0" << endl;
		delete[] ary;
	}
	return 0;
}

bool decAry(int a, int b) {
	return a > b;
}
