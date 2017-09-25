#include <iostream>
#include <fstream>
#include <algorithm> // max함수 이용
using namespace std;

int cardGame(int num, int *data, int **dp, int *sum);
void sumTable(int num, int *data, int *sum);

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
		// num+1만큼 동적할당 하는이유는 0행과 0열은 헷갈리니까 안쓸거임
		int *data = new int[num + 1];
		int *sum = new int[num + 1];
		int **dp = new int*[num + 1];
		for (int i = 0; i < num + 1; i++)
			dp[i] = new int[num + 1];

		data[0] = NULL;
		for (int i = 0; i <= num; i++) {
			if (i != 0)
				instream >> data[i];
			for (int j = 0; j <= num; j++)
				dp[i][j] = 0;
		}
		sumTable(num, data, sum); // sum 1차원배열을 만든다. (시간복잡도 줄이기 위함)
		cout << cardGame(num, data, dp, sum) << endl;
		// 메모리해제
		delete[] data;
		for (int i = 0; i < num + 1; i++)
			delete[] dp[i];
		delete[] dp;
		delete[] sum;
	}

	return 0;
}

int cardGame(int num, int *data, int **dp, int *sum) {
	// i==j 일 때 먼저 dp테이블을 채워넣는다. 같을 경우는 문제에서 주어진 값을 넣으면된다.
	for (int i = 1; i <= num; i++)
		dp[i][i] = data[i];
	for (int diagonal = 1; diagonal < num; diagonal++) {
		for (int i = 1; i <= num - diagonal; i++) {
			int j = i + diagonal;
			int s = sum[j] - sum[i - 1];
			dp[i][j] = max((s - dp[i + 1][j]), (s - dp[i][j - 1]));
		}
	}
	return dp[1][num];
}

void sumTable(int num, int *data, int *sum) {
	sum[0] = 0;
	sum[1] = data[1];
	for (int i = 2; i <= num; i++)
		sum[i] = sum[i - 1] + data[i];
}