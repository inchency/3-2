#include <iostream>
#include <fstream>
#include <algorithm> // sort ���� ����
#include <queue> // �켱���� ť ���� ����

using namespace std;

bool ascX1(class trail a, class trail b); // x1�� ���ؼ� �������� �������ִ� �Լ�
int priorityQ(class trail *t, int startIndex, int num, int range); // �켱���� ť�� �̿��� �ִ�� ��ø�Ǵ� ������ ã�� �Լ�

class trail {
public:
	int x0;
	int x1;
};

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
		trail *t = new trail[num];
		for (int i = 0; i < num; i++)
			instream >> t[i].x0 >> t[i].x1;
		int range;
		instream >> range;
		int cntt = 0;
		for (int i = 0; i < num; i++) {
			int a = t[i].x0;
			int b = t[i].x1;
			t[i].x0 = a < b ? a : b; // ������ ������
			t[i].x1 = a > b ? a : b; // ū�� �ڷ�
		}

		int notExistCnt = 0; // ���°��� �����ϰ� �����ϱ� ����
							 // �׽�Ʈ���̽��� �ſ� ū ���� -1��~1���̹Ƿ� �ð��ʰ��� �ɸ��� �������� ����ð��� �����̶� �ִ��� �Ʋ�����
		for (int i = 0, j = 0; i < num; i++) {
			if (t[i].x1 - t[i].x0 > range) {
				t[i].x0 = -100000001; // ��, ȸ���� �Ÿ��� -100000000 ~ 100000000 ����
				t[i].x1 = -100000001; // �Ѵ� -100000001�� ���༭ ������ �ƿ� �񱳸� ���� �ʰԲ� �Ѵ�.
				notExistCnt++;
			}
		}
		sort(t, t + num, ascX1); // x1�� ����������� �������� ����
		cout << priorityQ(t, notExistCnt, num, range) << endl;
		delete[] t;
	}
	return 0;
}

bool ascX1(class trail a, class trail b) {
	return a.x1 < b.x1;
}

int priorityQ(class trail *t, int startIndex, int num, int range) {
	int maxCnt = 0;
	priority_queue <int> priQ; // �켱����ť (���� ū���� top���� ���ĵǴ� Ư¡�� ����)
	for (int i = startIndex; i < num; i++) {
		priQ.push(-t[i].x0); // -�� ���ִ� ������ ���������� �񱳸� ���ְ� �ͱ� ����
							 // 2�� for���� �Ἥ �����ɸ� �� ������ �����δ� priQ�� ���� ��(size)�� ���� �ʰ� ö���� ���� �� �ִ� ������ break�� ���÷� �ɸ��� ������ ȿ������
		for (int j = 0; j < (int)priQ.size(); j++) {
			if (range >= t[i].x1 + priQ.top())
				break;
			priQ.pop();
		}
		maxCnt = maxCnt < (int)priQ.size() ? (int)priQ.size() : maxCnt;
	}
	return maxCnt;
}