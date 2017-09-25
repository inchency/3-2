#include <iostream>
#include <fstream>
#include <algorithm> // max�Լ� �̿�
using namespace std;

int cardGame(int num, int *data, int **dp, int *sum);
void sumTable(int num, int *data, int *sum);

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
		// num+1��ŭ �����Ҵ� �ϴ������� 0��� 0���� �򰥸��ϱ� �Ⱦ�����
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
		sumTable(num, data, sum); // sum 1�����迭�� �����. (�ð����⵵ ���̱� ����)
		cout << cardGame(num, data, dp, sum) << endl;
		// �޸�����
		delete[] data;
		for (int i = 0; i < num + 1; i++)
			delete[] dp[i];
		delete[] dp;
		delete[] sum;
	}

	return 0;
}

int cardGame(int num, int *data, int **dp, int *sum) {
	// i==j �� �� ���� dp���̺��� ä���ִ´�. ���� ���� �������� �־��� ���� ������ȴ�.
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