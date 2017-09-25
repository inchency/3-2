#include <iostream>
#include <fstream>
#define MARK 1
#define UNMARK 0

using namespace std;

class Point {
private:
	int x, y;
public:
	void setXY(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
};

bool knightTour(int m, int n, Point pos, int counter, Point *direction, int **board, int **path);
void printTour(int m, int n, int **path);

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt�� �� �� �����ϴ�." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int numCases = 0; numCases < cases; numCases++) {
		int x, y, sx, sy; // x�� ������ ũ�� y�� ������ ũ�� sx�� ������ġ x��ǥ sy�� ������ġ y��ǥ
		instream >> y >> x >> sx >> sy;
		sx -= 1; // ���� �迭�� 0���� �����ϹǷ�
		sy -= 1;
		Point dir[8];
		dir[0].setXY(1, -2); dir[1].setXY(2, -1); dir[2].setXY(2, 1); dir[3].setXY(1, 2);
		dir[4].setXY(-1, 2); dir[5].setXY(-2, 1); dir[6].setXY(-2, -1); dir[7].setXY(-1, -2);
		int **board = new int*[y]; // y,x 2���� �迭 ���� �Ҵ�
		int **path = new int*[y]; // y,x 2���� �迭 ���� �Ҵ�
		for (int i = 0; i < y; i++) {
			board[i] = new int[x]; // board ������ �迭�� �������� ���������� MARK Check
			path[i] = new int[x]; // path ������ �迭�� ���� ���� ���
		}
		for (int i = 0; i < y; i++) { // UNMARK�� �ʱ�ȭ
			for (int j = 0; j < x; j++) {
				board[i][j] = UNMARK;
				path[i][j] = UNMARK;
			}
		}
		Point start; // ������ġ
		start.setXY(sx, sy);
		board[sx][sy] = MARK; // ������ġ MARK ���ش�.
		path[sx][sy] = 1; // ���� ���� 1�� ���ش�.
		if (knightTour(y, x, start, 1, dir, board, path))
			printTour(y, x, path);
		else
			cout << "0" << endl;
	}
	return 0;
}

bool knightTour(int m, int n, Point pos, int counter, Point *direction, int **board, int **path) { // m�� �హ��, n�� ������, counter�� �̵�����
	Point next;
	if (counter == m * n) // 2���� �迭�� �� ����
		return true; // true ��ȯ
	for (int i = 0; i < 8; i++) { // �̵��� �� �ִ� ����� ���� 8���� �̹Ƿ�
		next.setX(pos.getX() + direction[i].getX());
		next.setY(pos.getY() + direction[i].getY());
		if (next.getX() >= 0 && next.getX() < m && next.getY() >= 0 && next.getY() < n && board[next.getX()][next.getY()] == UNMARK) { // �迭�� ���� �� �� �ְ� UNMARK ���¶��
			board[next.getX()][next.getY()] = MARK; // �������ٴ� MARK ǥ�� ���ְ�
			path[next.getX()][next.getY()] = counter + 1; // ������ ���� ǥ�� ���ش�.
			if (knightTour(m, n, next, counter + 1, direction, board, path)) // ����� �ݺ� �ؼ� true ���� ������
				return true; // true ��ȯ
			board[next.getX()][next.getY()] = UNMARK; // return true�� �ƴ϶�� �� ���� �ƴѰ��̹Ƿ� �ٽ� �� ���� UNMARK
		}
	}
	return false;
}

void printTour(int m, int n, int **path) {
	cout << "1" << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << path[i][j] << " ";
		}
		cout << endl;
	}
}