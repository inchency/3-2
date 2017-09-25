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
		dir[0].setXY(-1, -2); dir[1].setXY(-2, -1); dir[2].setXY(-2, 1); dir[3].setXY(-1, 2);
		dir[4].setXY(1, 2); dir[5].setXY(2, 1); dir[6].setXY(2, -1); dir[7].setXY(1, -2);
		int **board = new int*[y]; // y,x 2차원 배열 동적 할당
		int **path = new int*[y]; // y,x 2차원 배열 동적 할당
		Point **dirAry = new Point*[y];
		Point **check = new Point*[y];
		for (int i = 0; i < y; i++) {
			board[i] = new int[x]; // board 이차원 배열은 지나갔나 안지나갔나 MARK Check
			path[i] = new int[x]; // path 이차원 배열은 가는 순서 기록
			check[i] = new Point[x];
			dirAry[i] = new Point[x]; // dir을 저장할 2차원 배열
		}
		for (int i = 0; i < y; i++) { // 초기화
			for (int j = 0; j < x; j++) {
				board[i][j] = UNMARK;
				path[i][j] = 0;
				dirAry[i][j].setXY(NULL, NULL);
				//for (int k = 0; k < 8; k++)
				//check[i][j].c[k] = true; // 맨 처음은 모두 true로 초기화
				check[i][j].c[0] = true; check[i][j].c[1] = true; check[i][j].c[2] = true; check[i][j].c[3] = true; // 맨 처음은 모두 true로 초기화
				check[i][j].c[4] = true; check[i][j].c[5] = true; check[i][j].c[6] = true; check[i][j].c[7] = true;
			}
		}
		Point start; // 시작위치
		start.setXY(sx, sy);
		board[sx][sy] = MARK; // 시작위치 MARK 해준다.
		path[sx][sy] = 1; // 시작 순서 1로 해준다.
		if (knightTour(y, x, start, 1, dir, board, path, check, dirAry, sx, sy))
			printTour(y, x, path);
		else
			cout << "0" << endl;
	}
	return 0;
}

bool knightTour(int m, int n, Point pos, int counter, Point *direction, int **board, int **path, Point **check, Point **dirAry, int sx, int sy) { // m은 행갯수, n은 열갯수, counter은 이동순서
	Point next;
	int a = sx;
	int b = sy; // 임시 생성 변수
	while (1) {
		if (counter == m * n) // 2차원 배열에 꽉 차면
			return true; // true 반환하고 함수 종료
		for (int i = 0; i < 8; i++) { // 이동할 수 있는 경우의 수가 8가지 이므로
			next.setX(pos.getX() + direction[i].getX());
			next.setY(pos.getY() + direction[i].getY());
			if (next.getX() >= 0 && next.getX() < m && next.getY() >= 0 && next.getY() < n && board[next.getX()][next.getY()] == UNMARK && check[pos.getX()][pos.getY()].c[i] == true) { // 배열판 내에 들어갈 수 있고 UNMARK 상태라면
				dirAry[next.getX()][next.getY()].setXY(direction[i].getX(), direction[i].getY());
				board[next.getX()][next.getY()] = MARK; // 지나갔다는 MARK 표시 해주고
				counter++; // counter값 1 증가
				path[next.getX()][next.getY()] = counter; // 지나간 순서 표시 해준다.
				check[pos.getX()][pos.getY()].c[i] = false; // 실패시 반복하는 것을 막기 위해
				pos.setXY(next.getX(), next.getY()); // pos의 x,y를 바꾸어준다.
				break;
			}
			else if (i == 7) { // 8개의 경로 다 해봤는데도 안될 경우
				if (pos.getX() == sx && pos.getY() == sy)  // 안되는 경우가 시작점일 경우
					return false; // false를 리턴하고 함수 종료(이 경우는 불가능한 경로)
				board[pos.getX()][pos.getY()] = UNMARK; // 8번을 다 했는데 안된다면 그 길은 아닌것이므로 다시 그 길은 UNMARK
				counter--; // counter값 1 감소
				a = pos.getX(); // 임시 저장 변수 a
				b = pos.getY(); // 임시 저장 변수 b
				pos.setXY(pos.getX() - dirAry[pos.getX()][pos.getY()].getX(), pos.getY() - dirAry[pos.getX()][pos.getY()].getY());
				dirAry[a][b].setXY(NULL, NULL); // 다시 NULL로 초기화
												//for (int j = 0; j < 8; j++)
												//check[a][b].c[j] = true; // 다시 true로 초기화 해준다.
				check[a][b].c[0] = true; check[a][b].c[1] = true; check[a][b].c[2] = true; check[a][b].c[3] = true; // 다시 true로 초기화 해준다.
				check[a][b].c[4] = true; check[a][b].c[5] = true; check[a][b].c[6] = true; check[a][b].c[7] = true; // 다시 true로 초기화 해준다.
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