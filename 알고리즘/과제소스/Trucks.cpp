#include <iostream>
#include <fstream>
using namespace std;

int timeResult = 0;

bool isEmpty(int *b, int len);
bool isFull(int *b, int len);
void inq(int *b, int len, int item);
void deq(int *b, int len);

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt를 열 수 없습니다." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int testCases = 0; testCases < cases; testCases++) {
		int n, w, l;
		//cin >> n >> w >> l;
		instream >> n >> w >> l; // n:트럭의갯수 w:다리길이 l:다리최대하중
								 // int ary[1000] = { 0 };
		int *ary = new int[n]; // 트럭 무게를 저장할 배열
		for (int i = 0; i < n; i++)
			ary[i] = 0;
		for (int i = 0; i < n; i++)
			instream >> ary[i];
		int *bq = new int[w]; // 다리의 길이
		for (int i = 0; i < w; i++)
			bq[i] = 0;
		inq(bq, w, ary[0]);
		int i = 1;
		while (!isEmpty(bq, w)) {
			if (i == n) {
				while (1) {
					if (isEmpty(bq, w))
						break;
					deq(bq, w);
				}
				break;
			}
			int sum = 0;
			for (int j = 0; j < w; j++)
				sum += bq[j];
			if (sum + ary[i] <= l) {
				if (isFull(bq, w)) {
					deq(bq, w);
					inq(bq, w, ary[i]);
					i++;
					timeResult--;
				}
				else {
					inq(bq, w, ary[i]);
					i++;
				}
			}
			else {
				deq(bq, w);
				sum = 0;
				for (int j = 0; j < w; j++)
					sum += bq[j];
				if (sum + ary[i] <= l) {
					inq(bq, w, ary[i]);
					i++;
					timeResult--;
				}
			}
		}
		cout << timeResult << endl;
		delete[] bq;
		timeResult = 0; // timeResult 초기화
	}
	return 0;
}

bool isEmpty(int *b, int len) {
	for (int i = 0; i < len; i++) {
		if (b[i] != 0)
			return false;
	}
	return true;
}

bool isFull(int *b, int len) {
	for (int i = 0; i < len; i++) {
		if (b[i] == 0)
			return false;
	}
	return true;
}

void inq(int *b, int len, int item) {
	if (isFull(b, len)) {
		deq(b, len);
	}
	else {
		if (b[len - 1] == 0) {
			b[len - 1] = item;
			timeResult++;
		}
		else {
			for (int i = 0; i < len - 1; i++)
				b[i] = b[i + 1];
			b[len - 1] = item;
			timeResult++;
		}
	}
}

void deq(int *b, int len) {
	for (int i = 0; i < len - 1; i++)
		b[i] = b[i + 1];
	b[len - 1] = 0;
	timeResult++;
}