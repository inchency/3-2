#include <iostream>
#include <fstream>
using namespace std;
#define MAX_COINS 101
#define MAX_CHANGE 1001

int countCoinExchange(int *coins, int numDiffCoins, int change);

int main() {
	ifstream instream;
	instream.open("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt�� �� �� �����ϴ�." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int testCases = 0; testCases < cases; testCases++) {
		int num; // ������ ����
		int change; // �Ž�����
		instream >> num;
		int *coinDiff = new int[num]; // ������ �迭 
		for (int i = 0; i < num; i++)
			instream >> coinDiff[i];
		instream >> change;
		cout << countCoinExchange(coinDiff, num, change) << endl;
	}
	return 0;
}

int countCoinExchange(int *coins, int numDiffCoins, int change) {
	int numComb;
	int **coinTable = new int*[numDiffCoins + 1];
	for (int i = 0; i < numDiffCoins + 1; i++)
		coinTable[i] = new int[change + 1];
	// �������̺� 2�����迭�� �����Ҵ��ϱ� ũ��� ��������+1, �Ž�����+1 (���̺� 0�� ���ϱ� +1��)
	for (int i = 0; i <= numDiffCoins; i++) {
		for (int j = 0; j <= change; j++) {
			if (j == 0)
				coinTable[i][j] = 1;
			else if (j > 0 && i == 0)
				coinTable[i][j] = 0;
			else
				coinTable[i][j] = NULL;
		}
	}
	// base case and ���̺� �ʱ�ȭ
	for (int i = 1; i <= numDiffCoins; i++) {
		for (int j = 1; j <= change; j++) {
			if (j - coins[i - 1] < 0) // base case
				numComb = 0;
			else
				numComb = coinTable[i][j - coins[i - 1]];
			coinTable[i][j] = coinTable[i - 1][j] + numComb;
		}
	}
	/*for (int i = 0; i <= numDiffCoins; i++) {
	for (int j = 0; j <= change; j++)
	cout << coinTable[i][j] << " ";
	cout << endl;
	}
	return 0;*/
	return coinTable[numDiffCoins][change];
}