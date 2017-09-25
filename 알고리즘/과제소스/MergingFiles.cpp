#include <iostream>
#include <fstream>
using namespace std;

int mergeFile(int *ary, int num);

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
		int *ary = new int[num + 1]; // input 데이터 파일을 받는 배열
		for (int i = 1; i <= num; i++)
			instream >> ary[i];
		cout << mergeFile(ary, num) << endl;
		delete[] ary;
	}
	return 0;
}

int mergeFile(int *ary, int num) {
	int mergeTable[501][501] = { 0 };
	bool flag;
	for (int diagonal = 1; diagonal <= num - 1; diagonal++) {
		for (int i = 1; i <= num - diagonal; i++) {
			int j = i + diagonal; // 맨 끝의 index
			int sum = 0;
			for (int k = i; k <= j; k++)
				sum += ary[k];
			flag = true;
			for (int k = i; k < j; k++) {
				if (flag) {
					mergeTable[i][j] = mergeTable[i][k] + mergeTable[k + 1][j];
					flag = false;
				}
				mergeTable[i][j] = mergeTable[i][j] > mergeTable[i][k] + mergeTable[k + 1][j] ? mergeTable[i][k] + mergeTable[k + 1][j] : mergeTable[i][j];
			}
			mergeTable[i][j] += sum;
		}
	}
	return mergeTable[1][num];
}