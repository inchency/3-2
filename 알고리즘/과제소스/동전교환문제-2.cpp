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
		cout << "input.txt를 열 수 없습니다." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int testCases = 0; testCases < cases; testCases++) {
		int num; // 동전의 갯수
		int change; // 거스름돈
		instream >> num;
		int *coinDiff = new int[num]; // 동전의 배열 
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
	// 코인테이블 2차원배열로 동적할당하기 크기는 동전갯수+1, 거스름돈+1 (테이블에 0도 들어가니까 +1씩)
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
	// base case and 테이블 초기화
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