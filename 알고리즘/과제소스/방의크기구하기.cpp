#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

class go {
public:
	int x, y;
};
bool decAry(int a, int b); // 내림차순 정렬
void emptyRoom(char **ary, go *dir, int sizeX, int sizeY, go pos, bool check);
int cnt = 1; // 방의 종류의 갯수
int cntRoom = 0; // 같은 종류의 방의 갯수
int cntRoomAry[100] = { 0 };
int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt를 열 수 없습니다." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int testCases = 0; testCases < cases; testCases++) {
		int x, y; // x=행, y=열
		instream >> y >> x;
		char **ary = new char*[x];
		for (int i = 0; i < x; i++)
			ary[i] = new char[y]; // 2차원 배열 동적할당
		for (int i = 0; i < x; i++) { // 데이터 읽기
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
				if (ary[i][j] == '.') { // 시작 .을 잡아준다
					start.x = i; // 시작 x 좌표
					start.y = j; // 시작 y 좌표
					ary[start.x][start.y] = '+'; // +로 바꿔주고
					flag = true;
					break;
				}
			}
		}
		emptyRoom(ary, dir, x, y, start, true); // check는 처음 실행 하는 함수가 끝날때를 알기 위해
		cout << cnt << endl; // 방의 종류의 갯수 출력
		cnt = 1; // 방의 갯수 초기화
		sort(cntRoomAry, cntRoomAry + 100, decAry);
		for (int i = 0; i < 100; i++) {
			if (cntRoomAry[i] == 0)
				break;
			cout << cntRoomAry[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 100; i++) // 초기화
			cntRoomAry[i] = 0;
	}
	return 0;
}

void emptyRoom(char **ary, go *dir, int sizeX, int sizeY, go pos, bool check) {
	cntRoom++;
	go next; // 다음 좌표를 저장함
	bool flag = false; // 2중for문 break 걸기 위함
	for (int i = 0; i < 4; i++) {
		next.x = pos.x + dir[i].x; // 다음의 x 좌표
		next.y = pos.y + dir[i].y; // 다음의 y 좌표
		if (ary[next.x][next.y] == '.') { // '.'이면 (방이면)
			ary[next.x][next.y] = '+'; // +로 바꿔주고
			emptyRoom(ary, dir, sizeX, sizeY, next, false); // recursive한 check 값은 false이다
		}
	}
	if (check) { // 방 검사가 끝났으면
		for (int z = 0; z < 100; z++) {
			if (cntRoomAry[z] == 0) {
				cntRoomAry[z] = cntRoom;
				break;
			}
		}
		cntRoom = 0; // 방의 갯수 초기화
		for (int i = 0; i < sizeX; i++) {
			if (flag)
				break;
			for (int j = 0; j < sizeY; j++) {
				if (ary[i][j] == '.') { // 시작 .을 잡아준다
					cnt++;
					pos.x = i; // 시작 x 좌표
					pos.y = j; // 시작 y 좌표
					ary[pos.x][pos.y] = '+'; // +로 바꿔주고
					flag = true;
					// 방이 더 남아 있는 경우
					emptyRoom(ary, dir, sizeX, sizeY, pos, true); // 함수 recursive 하게 계속 실행
					break;
				}
			}
		}
	}

}

bool decAry(int a, int b) {
	return a > b;
}