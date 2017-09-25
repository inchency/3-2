#include <iostream>
#include <fstream>
using namespace std;

class coinTable {
public:
	int coinUsed;
	int lastCoin;
};

void minChange(int change, int num, int *coinDiff, coinTable *cointable, int min); // 최소 동전 갯수 계산 함수
void reconstruct(int change, coinTable *cointable, int *countCoin, int num, int *coinDiff);
int findMin(int *coinDiff, int num); // 최소값 찾는 함수

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt를 열 수 없습니다." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int testCases = 0; testCases < cases; testCases++) {
		int num; // 동전의 갯수
		instream >> num;
		int *coinDiff = new int[num]; // 동전 갯수만큼 배열 크기 동적할당
		for (int testNum = 0; testNum < num; testNum++)
			instream >> coinDiff[testNum];
		int change; // 총 거스름돈
					//int minChange = 0; // 거스름돈 최소로 하는 변수
		instream >> change;
		int min = findMin(coinDiff, num);
		coinTable *cointable = new coinTable[change + 1];
		minChange(change, num, coinDiff, cointable, min);
		/*for (int i = 0; i <= change; i++)
		cout << i << ": " << cointable[i].coinUsed << " " << cointable[i].lastCoin << endl;*/
		int *countCoin = new int[num];
		// countCoin이라는 배열 만들어서 각각의 동전이 총 몇개 쓰이는지를 등록할건데 0으로 초기화
		for (int i = 0; i < num; i++)
			countCoin[i] = 0;
		reconstruct(change, cointable, countCoin, num, coinDiff);
		cout << cointable[change].coinUsed << endl;
		for (int i = 0; i < num; i++)
			cout << countCoin[i] << " ";
		cout << endl;
		delete[]cointable;
		delete[]countCoin;
	}
	return 0;
}
// change는 거스름돈, num은 거스름돈가능한 동전갯수, coinDiff는 동전종류배열, cointable은 테이블저장할 클래스배열, min은 교환가능동전중 최소값
void minChange(int change, int num, int *coinDiff, coinTable *cointable, int min) {
	cointable[0].coinUsed = 0;
	cointable[0].lastCoin = 0;
	for (int cents = min; cents <= change; cents++) {
		int minCoins, newCoin;
		minCoins = cents;
		newCoin = min;
		for (int j = 0; j < num; j++) {
			if (coinDiff[j] > cents)
				continue;
			if (cointable[cents - coinDiff[j]].coinUsed + 1 <= minCoins) { // 테이블에서 더 작은 경우가 생기면 minCoins를 계속 줄여나감
				minCoins = cointable[cents - coinDiff[j]].coinUsed + 1;
				newCoin = coinDiff[j];
			}
		}
		cointable[cents].coinUsed = minCoins;
		cointable[cents].lastCoin = newCoin;
	}
}

void reconstruct(int change, coinTable *cointable, int *countCoin, int num, int *coinDiff) {
	if (change > 0) {
		reconstruct(change - cointable[change].lastCoin, cointable, countCoin, num, coinDiff);
		for (int i = 0; i < num; i++) {
			if (coinDiff[i] == cointable[change].lastCoin)
				countCoin[i]++;
		}
		//cout << cointable[change].lastCoin << endl;
	}
}

int findMin(int *coinDiff, int num) {
	int min = coinDiff[0];
	for (int i = 1; i < num; i++) {
		if (min > coinDiff[i])
			min = coinDiff[i];
	}
	return min;
}