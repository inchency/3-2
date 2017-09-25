#include <iostream>
#include <fstream>
#define MARK 1
#define UNMARK 0

using namespace std;

class Point {
private:
	int x, y;
public:
	bool c[8];
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


bool knightTour(int m, int n, Point pos, int counter, Point *direction, int **board, int **path, Point **check, Point **dirAry, int sx, int sy);
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
		dir[0].setXY(-1, -2); dir[1].setXY(-2, -1); dir[2].setXY(-2, 1); dir[3].setXY(-1, 2);
		dir[4].setXY(1, 2); dir[5].setXY(2, 1); dir[6].setXY(2, -1); dir[7].setXY(1, -2);
		int **board = new int*[y]; // y,x 2���� �迭 ���� �Ҵ�
		int **path = new int*[y]; // y,x 2���� �迭 ���� �Ҵ�
		Point **dirAry = new Point*[y];
		Point **check = new Point*[y];
		for (int i = 0; i < y; i++) {
			board[i] = new int[x]; // board ������ �迭�� �������� ���������� MARK Check
			path[i] = new int[x]; // path ������ �迭�� ���� ���� ���
			check[i] = new Point[x];
			dirAry[i] = new Point[x]; // dir�� ������ 2���� �迭
		}
		for (int i = 0; i < y; i++) { // �ʱ�ȭ
			for (int j = 0; j < x; j++) {
				board[i][j] = UNMARK;
				path[i][j] = 0;
				dirAry[i][j].setXY(NULL, NULL);
				//for (int k = 0; k < 8; k++)
				//check[i][j].c[k] = true; // �� ó���� ��� true�� �ʱ�ȭ
				check[i][j].c[0] = true; check[i][j].c[1] = true; check[i][j].c[2] = true; check[i][j].c[3] = true; // �� ó���� ��� true�� �ʱ�ȭ
				check[i][j].c[4] = true; check[i][j].c[5] = true; check[i][j].c[6] = true; check[i][j].c[7] = true;
			}
		}
		Point start; // ������ġ
		start.setXY(sx, sy);
		board[sx][sy] = MARK; // ������ġ MARK ���ش�.
		path[sx][sy] = 1; // ���� ���� 1�� ���ش�.
		if (knightTour(y, x, start, 1, dir, board, path, check, dirAry, sx, sy))
			printTour(y, x, path);
		else
			cout << "0" << endl;
	}
	return 0;
}

bool knightTour(int m, int n, Point pos, int counter, Point *direction, int **board, int **path, Point **check, Point **dirAry, int sx, int sy) { // m�� �హ��, n�� ������, counter�� �̵�����
	Point next;
	int a = sx;
	int b = sy; // �ӽ� ���� ����
	while (1) {
		if (counter == m * n) // 2���� �迭�� �� ����
			return true; // true ��ȯ�ϰ� �Լ� ����
		for (int i = 0; i < 8; i++) { // �̵��� �� �ִ� ����� ���� 8���� �̹Ƿ�
			next.setX(pos.getX() + direction[i].getX());
			next.setY(pos.getY() + direction[i].getY());
			if (next.getX() >= 0 && next.getX() < m && next.getY() >= 0 && next.getY() < n && board[next.getX()][next.getY()] == UNMARK && check[pos.getX()][pos.getY()].c[i] == true) { // �迭�� ���� �� �� �ְ� UNMARK ���¶��
				dirAry[next.getX()][next.getY()].setXY(direction[i].getX(), direction[i].getY());
				board[next.getX()][next.getY()] = MARK; // �������ٴ� MARK ǥ�� ���ְ�
				counter++; // counter�� 1 ����
				path[next.getX()][next.getY()] = counter; // ������ ���� ǥ�� ���ش�.
				check[pos.getX()][pos.getY()].c[i] = false; // ���н� �ݺ��ϴ� ���� ���� ����
				pos.setXY(next.getX(), next.getY()); // pos�� x,y�� �ٲپ��ش�.
				break;
			}
			else if (i == 7) { // 8���� ��� �� �غôµ��� �ȵ� ���
				if (pos.getX() == sx && pos.getY() == sy)  // �ȵǴ� ��찡 �������� ���
					return false; // false�� �����ϰ� �Լ� ����(�� ���� �Ұ����� ���)
				board[pos.getX()][pos.getY()] = UNMARK; // 8���� �� �ߴµ� �ȵȴٸ� �� ���� �ƴѰ��̹Ƿ� �ٽ� �� ���� UNMARK
				counter--; // counter�� 1 ����
				a = pos.getX(); // �ӽ� ���� ���� a
				b = pos.getY(); // �ӽ� ���� ���� b
				pos.setXY(pos.getX() - dirAry[pos.getX()][pos.getY()].getX(), pos.getY() - dirAry[pos.getX()][pos.getY()].getY());
				dirAry[a][b].setXY(NULL, NULL); // �ٽ� NULL�� �ʱ�ȭ
												//for (int j = 0; j < 8; j++)
												//check[a][b].c[j] = true; // �ٽ� true�� �ʱ�ȭ ���ش�.
				check[a][b].c[0] = true; check[a][b].c[1] = true; check[a][b].c[2] = true; check[a][b].c[3] = true; // �ٽ� true�� �ʱ�ȭ ���ش�.
				check[a][b].c[4] = true; check[a][b].c[5] = true; check[a][b].c[6] = true; check[a][b].c[7] = true; // �ٽ� true�� �ʱ�ȭ ���ش�.
			}
		}
	}
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