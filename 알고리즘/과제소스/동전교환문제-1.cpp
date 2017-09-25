#include <iostream>
#include <fstream>
using namespace std;

class coinTable {
public:
	int coinUsed;
	int lastCoin;
};

void minChange(int change, int num, int *coinDiff, coinTable *cointable, int min); // �ּ� ���� ���� ��� �Լ�
void reconstruct(int change, coinTable *cointable, int *countCoin, int num, int *coinDiff);
int findMin(int *coinDiff, int num); // �ּҰ� ã�� �Լ�

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt�� �� �� �����ϴ�." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int testCases = 0; testCases < cases; testCases++) {
		int num; // ������ ����
		instream >> num;
		int *coinDiff = new int[num]; // ���� ������ŭ �迭 ũ�� �����Ҵ�
		for (int testNum = 0; testNum < num; testNum++)
			instream >> coinDiff[testNum];
		int change; // �� �Ž�����
					//int minChange = 0; // �Ž����� �ּҷ� �ϴ� ����
		instream >> change;
		int min = findMin(coinDiff, num);
		coinTable *cointable = new coinTable[change + 1];
		minChange(change, num, coinDiff, cointable, min);
		/*for (int i = 0; i <= change; i++)
		cout << i << ": " << cointable[i].coinUsed << " " << cointable[i].lastCoin << endl;*/
		int *countCoin = new int[num];
		// countCoin�̶�� �迭 ���� ������ ������ �� � ���̴����� ����Ұǵ� 0���� �ʱ�ȭ
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
// change�� �Ž�����, num�� �Ž����������� ��������, coinDiff�� ���������迭, cointable�� ���̺������� Ŭ�����迭, min�� ��ȯ���ɵ����� �ּҰ�
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
			if (cointable[cents - coinDiff[j]].coinUsed + 1 <= minCoins) { // ���̺��� �� ���� ��찡 ����� minCoins�� ��� �ٿ�����
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