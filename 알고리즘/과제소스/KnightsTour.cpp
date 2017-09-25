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
		cout << "input.txt를 열 수 없습니다." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int numCases = 0; numCases < cases; numCases++) {
		int x, y, sx, sy; // x는 가로의 크기 y는 세로의 크기 sx는 시작위치 x좌표 sy는 시작위치 y좌표
		instream >> y >> x >> sx >> sy;
		sx -= 1; // 실제 배열은 0부터 시작하므로
		sy -= 1;
		Point dir[8];
		dir[0].setXY(1, -2); dir[1].setXY(2, -1); dir[2].setXY(2, 1); dir[3].setXY(1, 2);
		dir[4].setXY(-1, 2); dir[5].setXY(-2, 1); dir[6].setXY(-2, -1); dir[7].setXY(-1, -2);
		int **board = new int*[y]; // y,x 2차원 배열 동적 할당
		int **path = new int*[y]; // y,x 2차원 배열 동적 할당
		for (int i = 0; i < y; i++) {
			board[i] = new int[x]; // board 이차원 배열은 지나갔나 안지나갔나 MARK Check
			path[i] = new int[x]; // path 이차원 배열은 가는 순서 기록
		}
		for (int i = 0; i < y; i++) { // UNMARK로 초기화
			for (int j = 0; j < x; j++) {
				board[i][j] = UNMARK;
				path[i][j] = UNMARK;
			}
		}
		Point start; // 시작위치
		start.setXY(sx, sy);
		board[sx][sy] = MARK; // 시작위치 MARK 해준다.
		path[sx][sy] = 1; // 시작 순서 1로 해준다.
		if (knightTour(y, x, start, 1, dir, board, path))
			printTour(y, x, path);
		else
			cout << "0" << endl;
	}
	return 0;
}

bool knightTour(int m, int n, Point pos, int counter, Point *direction, int **board, int **path) { // m은 행갯수, n은 열갯수, counter은 이동순서
	Point next;
	if (counter == m * n) // 2차원 배열에 꽉 차면
		return true; // true 반환
	for (int i = 0; i < 8; i++) { // 이동할 수 있는 경우의 수가 8가지 이므로
		next.setX(pos.getX() + direction[i].getX());
		next.setY(pos.getY() + direction[i].getY());
		if (next.getX() >= 0 && next.getX() < m && next.getY() >= 0 && next.getY() < n && board[next.getX()][next.getY()] == UNMARK) { // 배열판 내에 들어갈 수 있고 UNMARK 상태라면
			board[next.getX()][next.getY()] = MARK; // 지나갔다는 MARK 표시 해주고
			path[next.getX()][next.getY()] = counter + 1; // 지나간 순서 표시 해준다.
			if (knightTour(m, n, next, counter + 1, direction, board, path)) // 재귀적 반복 해서 true 값이 나오면
				return true; // true 반환
			board[next.getX()][next.getY()] = UNMARK; // return true가 아니라면 그 길은 아닌것이므로 다시 그 길은 UNMARK
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