#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

bool decAry(int a, int b);

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
		int *ary = new int[num];
		for (int i = 0; i < num; i++)
			instream >> ary[i];
		sort(ary, ary + num, decAry);
		/*for (int i = 0; i < num; i++)
		cout << ary[i] << " ";
		cout << endl;*/
		int QIndex, bigCnt = 0, smallCnt = 0, flag = false, flag2 = false; // 큐인덱스, 인덱스이상인거 카운트, 인덱스 이하인거 카운트, 인덱스 이상인거 다찾으면 flag = false하고 small인거 체크시작, flag2는 QIndex가 없으면
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
