#include <iostream>
#include <fstream>

using namespace std;

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
		int floor, num, cnt; // ���ʷ� ��, ������ ����, �� ����� ����
		instream >> floor >> num >> cnt;
		int **ary = new int*[floor];
		for (int i = 0; i < floor; i++)
			ary[i] = new int[num]; // ��, �氹����ŭ 2���� �����Ҵ�
		for (int i = 0; i < floor; i++) {
			for (int j = 0; j < num; j++) {
				ary[i][j] = (i + 1) * 100 + (j + 1);
			}
		}
		// ������ ä��°��̹Ƿ� cnt�� floor��ŭ ������ ���� �� ���� ������ ���ȣ�� ���Ѵ�.
		bool flag = false; // �� ���� ����� �� ��� �ʱⰪ�� false
		int row, col;
		if (cnt % floor == 0)
			flag = true; // ��������� ��
		if (!flag) {
			row = cnt / floor; // ���η� ���ȣ 
			col = cnt % floor - 1; // ���η� ������ -1�� ������ �迭���� ���ϱ�����
		}
		else { // ����⿡ ���� ���� ��
			row = cnt / floor - 1; // ���η� ���ȣ
			col = floor - 1; // ���η� ���ȣ
		}
		cout << ary[col][row] << endl;
		delete[]ary;
	}
	return 0;
}