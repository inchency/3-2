#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class Cafe {
public:
	int x;
	int y;
};

void swap(int *a, int *b);
bool ascX(class Cafe a, class Cafe b);// x�� �������� �����Լ�
bool ascY(class Cafe a, class Cafe b); // x�� �������� �����Լ�
bool decY(class Cafe a, class Cafe b); // y�� �������� �����Լ�

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt�� �� �� �����ϴ�." << endl;
		return -1;
	}
	int testCases;
	instream >> testCases;
	for (int cases = 0; cases < testCases; cases++) {
		int num;
		instream >> num;
		Cafe *cafe = new Cafe[num]; // num��ŭ cafe��ü �����Ҵ�
		for (int initialization = 0; initialization < num; initialization++) { // num��ŭ �ʱ�ȭ
			cafe[initialization].x = 0;
			cafe[initialization].y = 0;
		}
		for (int i = 0; i < num; i++)
			instream >> cafe[i].x >> cafe[i].y;
		if (cafe[0].x != 0 || cafe[0].y != 0) { // ù ������ 0,0�� �ƴ϶��
			for (int i = 1; i < num; i++) { // 0,0�� ã�Ƽ� �� ������ �̾��ش�
				if (cafe[i].x == 0 && cafe[i].y == 0) {
					swap(cafe[0].x, cafe[i].x);
					swap(cafe[0].y, cafe[i].y);
				}
			}
		}
		sort(cafe + 1, cafe + num, ascX); // x �������� ����
		int cnt = 1;
		if (cafe[1].x == 0) { // 0,0 �̿ܿ� 0�� �����Ѵٸ�
			for (int i = 2; i < num; i++) {
				if (cafe[i].x != 0) // 0�� �ƴ� ���� ������
					break; // ã���ߴ�
				cnt++;
			}
			if (cafe[1].y < 0)  // -�̹Ƿ� �������� �׷��� �� �������� 
				sort(cafe + 1, cafe + cnt + 1, decY); // �������� ����
			else // �ö󰡴� �׷��� �� ��������
				sort(cafe + 1, cafe + cnt + 1, ascY); // �������� ����
		}
		// ������� ������ 0,0 && x �������� ���� �Ϸ� && x=0 �϶� y ���� �Ϸ�
		// �������� 0 �ʰ��� y������ �ؾ��Ѵ�
		for (int i = cnt; i < num; i++) {
			int store = i;
			int count = 1;
			if (cafe[i].x == cafe[i + 1].x) { // �ߺ��Ǵ� x���� ������
				for (int j = i + 1; j < num; j++) {
					if (cafe[j].x != cafe[store].x) // �ٸ����� ������
						break; // ã���ߴ�
					count++;
					i++;
				}
				for (int j = store + 1; j < num; j++) { // ���ʿ� �� y��� ������ �̶�� ������ �ʿ䰡 ����
					if (cafe[j].y == cafe[store - 1].y) { // �� y��� ���� ���� ã�´�
						swap(cafe[j].y, cafe[store].y);
						break;
					}
				}
				// ������� �ٸ����� ù��°�� ��ġ �Ϸ�
				if (cafe[store].y < cafe[store + 1].y) // �ö󰡴� �׷������
					sort(cafe + store, cafe + count + store, ascY); // �������� ����
				else // �������� �׷������
					sort(cafe + store, cafe + count + store, decY); // �������� ����
			}
		}
		//for (int i = 0; i < num; i++)
		//cout << cafe[i].x << " " << cafe[i].y << endl;

		int m; // ���ؾ��� ���� m
		instream >> m;
		for (int k = 0; k < m; k++) {
			int n; // ī���� ��ȣ n
			instream >> n;
			cout << cafe[n - 1].x << " " << cafe[n - 1].y; // -1 ���ִ� ������ ��ȣ�� 1�����ͽ����ϰ� �迭�� 0������ �����ϹǷ�
			cout << endl;
		}
	}
	return 0;
}

void swap(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

bool ascX(class Cafe a, class Cafe b) {
	return a.x < b.x;
}
bool ascY(class Cafe a, class Cafe b) {
	return a.y < b.y;
}
bool decY(class Cafe a, class Cafe b) {
	return a.y > b.y;
}