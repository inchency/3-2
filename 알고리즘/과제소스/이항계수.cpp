#include <iostream>
#include <fstream>
using namespace std;

int binomicalCoefficient(int a, int b);
int gcd(int a, int b); // �ִ����� ���ϴ� �Լ�

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt�� �� �� �����ϴ�." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int testCases = 0; testCases < cases; testCases++) {
		int N, K;
		instream >> N >> K;
		cout << binomicalCoefficient(N, K) << endl;
	}
	return 0;
}

int binomicalCoefficient(int a, int b) {
	if (a == b || b == 0) // ���� ���� ���װ���� 1�� Ȥ�� b�� 0�϶��� 1��
		return 1;
	else if (a / 2 < b)  // ex)20 Combination 17�� ��� -> 20 Combination 3���� ��ȯ
		b = a - b;
	int *aryA = new int[b]; // �� ���ؾ� �ؾ��� �迭�� �����Ҵ��ؼ� ����(����)
	int *aryB = new int[b]; // �� ���ؾ� �ؾ��� �迭�� �����Ҵ��ؼ� ����(�и�)
							// a�� ���� 20�̶�� 20,19,18 .... 2,1 �̷������� �����Ұ��� �� b�� ���� ������ŭ��
	int tempA = a;
	int tempB = b;
	for (int i = 0; i < b; i++, tempA--, tempB--) {
		aryA[i] = tempA;
		aryB[i] = tempB;
	}
	// ������� �迭�� ���� ���ڸ� �־���� ���� �и� �ִ� ���ڵ��� ����Ҽ������� ����ؾ��Ѵ�.
	int gcdAB; // �μ��� �ִ�����
	for (int i = 0; i < b; i++) { // �и𵵴� for��
		for (int j = 0; j < b; j++) { // ���ڵ��� for��
			gcdAB = gcd(aryA[j], aryB[i]);
			aryA[j] /= gcdAB;
			aryB[i] /= gcdAB;
			if (aryB[i] == 1) // 1�� �Ǹ� ���̻� for���� �� �ʿ䰡 ����
				break;
		}
	}
	// ������� �и�� �� 1�� ���ŵǾ��� ���ڸ� �������� ���� ����ϱ⿣ ���� �ʹ� Ŀ���� ������ ���Ƿ� �ѹ� ���ϰ� ���� �������� �����ɷ� ���ϴ� ������ �ݺ�
	int result = aryA[0];
	for (int i = 1; i < b; i++)
		result = result * aryA[i] % 10007;
	return result;
}

int gcd(int a, int b) {
	if (b == 0)
		return a;
	else
		return gcd(b, a%b);
}