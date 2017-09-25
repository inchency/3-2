#include <iostream>
#include <fstream>
#include <algorithm> // sort 쓰기 위함
#include <queue> // 우선순위 큐 쓰기 위함

using namespace std;

bool ascX1(class trail a, class trail b); // x1에 대해서 오름차순 정렬해주는 함수
int priorityQ(class trail *t, int startIndex, int num, int range); // 우선순위 큐를 이용해 최대로 중첩되는 갯수를 찾는 함수

class trail {
public:
	int x0;
	int x1;
};

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
		trail *t = new trail[num];
		for (int i = 0; i < num; i++)
			instream >> t[i].x0 >> t[i].x1;
		int range;
		instream >> range;
		int cntt = 0;
		for (int i = 0; i < num; i++) {
			int a = t[i].x0;
			int b = t[i].x1;
			t[i].x0 = a < b ? a : b; // 작은게 앞으로
			t[i].x1 = a > b ? a : b; // 큰게 뒤로
		}

		int notExistCnt = 0; // 없는값은 제외하고 시작하기 위함
							 // 테스트케이스가 매우 큰 범위 -1억~1억이므로 시간초과에 걸리지 않으려면 실행시간을 조금이라도 최대한 아껴야함
		for (int i = 0, j = 0; i < num; i++) {
			if (t[i].x1 - t[i].x0 > range) {
				t[i].x0 = -100000001; // 집, 회사의 거리는 -100000000 ~ 100000000 사이
				t[i].x1 = -100000001; // 둘다 -100000001로 해줘서 다음에 아예 비교를 하지 않게끔 한다.
				notExistCnt++;
			}
		}
		sort(t, t + num, ascX1); // x1이 작은순서대로 오름차순 소팅
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
	priority_queue <int> priQ; // 우선순위큐 (가장 큰값이 top으로 정렬되는 특징이 있음)
	for (int i = startIndex; i < num; i++) {
		priQ.push(-t[i].x0); // -를 해주는 이유는 작은값부터 비교를 해주고 싶기 때문
							 // 2중 for문을 써서 오래걸릴 것 같지만 실제로는 priQ에 들어가는 값(size)이 많지 않고 철도를 놓을 수 있는 범위면 break가 수시로 걸리기 때문에 효율적임
		for (int j = 0; j < (int)priQ.size(); j++) {
			if (range >= t[i].x1 + priQ.top())
				break;
			priQ.pop();
		}
		maxCnt = maxCnt < (int)priQ.size() ? (int)priQ.size() : maxCnt;
	}
	return maxCnt;
}