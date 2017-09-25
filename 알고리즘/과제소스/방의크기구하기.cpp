#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

class go {
public:
	int x, y;
};
bool decAry(int a, int b); // �������� ����
void emptyRoom(char **ary, go *dir, int sizeX, int sizeY, go pos, bool check);
int cnt = 1; // ���� ������ ����
int cntRoom = 0; // ���� ������ ���� ����
int cntRoomAry[100] = { 0 };
int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt�� �� �� �����ϴ�." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int testCases = 0; testCases < cases; testCases++) {
		int x, y; // x=��, y=��
		instream >> y >> x;
		char **ary = new char*[x];
		for (int i = 0; i < x; i++)
			ary[i] = new char[y]; // 2���� �迭 �����Ҵ�
		for (int i = 0; i < x; i++) { // ������ �б�
			for (int j = 0; j < y; j++)
				instream >> ary[i][j];
		}
		go dir[4];
		dir[0].x = -1; dir[0].y = 0;   dir[1].x = 0; dir[1].y = -1;   dir[2].x = 1; dir[2].y = 0;   dir[3].x = 0; dir[3].y = 1;
		go start;
		bool flag = false;
		for (int i = 0; i < x; i++) {
			if (flag)
				break;
			for (int j = 0; j < y; j++) {
				if (ary[i][j] == '.') { // ���� .�� ����ش�
					start.x = i; // ���� x ��ǥ
					start.y = j; // ���� y ��ǥ
					ary[start.x][start.y] = '+'; // +�� �ٲ��ְ�
					flag = true;
					break;
				}
			}
		}
		emptyRoom(ary, dir, x, y, start, true); // check�� ó�� ���� �ϴ� �Լ��� �������� �˱� ����
		cout << cnt << endl; // ���� ������ ���� ���
		cnt = 1; // ���� ���� �ʱ�ȭ
		sort(cntRoomAry, cntRoomAry + 100, decAry);
		for (int i = 0; i < 100; i++) {
			if (cntRoomAry[i] == 0)
				break;
			cout << cntRoomAry[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 100; i++) // �ʱ�ȭ
			cntRoomAry[i] = 0;
	}
	return 0;
}

void emptyRoom(char **ary, go *dir, int sizeX, int sizeY, go pos, bool check) {
	cntRoom++;
	go next; // ���� ��ǥ�� ������
	bool flag = false; // 2��for�� break �ɱ� ����
	for (int i = 0; i < 4; i++) {
		next.x = pos.x + dir[i].x; // ������ x ��ǥ
		next.y = pos.y + dir[i].y; // ������ y ��ǥ
		if (ary[next.x][next.y] == '.') { // '.'�̸� (���̸�)
			ary[next.x][next.y] = '+'; // +�� �ٲ��ְ�
			emptyRoom(ary, dir, sizeX, sizeY, next, false); // recursive�� check ���� false�̴�
		}
	}
	if (check) { // �� �˻簡 ��������
		for (int z = 0; z < 100; z++) {
			if (cntRoomAry[z] == 0) {
				cntRoomAry[z] = cntRoom;
				break;
			}
		}
		cntRoom = 0; // ���� ���� �ʱ�ȭ
		for (int i = 0; i < sizeX; i++) {
			if (flag)
				break;
			for (int j = 0; j < sizeY; j++) {
				if (ary[i][j] == '.') { // ���� .�� ����ش�
					cnt++;
					pos.x = i; // ���� x ��ǥ
					pos.y = j; // ���� y ��ǥ
					ary[pos.x][pos.y] = '+'; // +�� �ٲ��ְ�
					flag = true;
					// ���� �� ���� �ִ� ���
					emptyRoom(ary, dir, sizeX, sizeY, pos, true); // �Լ� recursive �ϰ� ��� ����
					break;
				}
			}
		}
	}

}

bool decAry(int a, int b) {
	return a > b;
}