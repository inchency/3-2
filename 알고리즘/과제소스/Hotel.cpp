#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream instream;
	instream.open("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt를 열 수 없습니다." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int testCases = 0; testCases < cases; testCases++) {
		int floor, num, cnt; // 차례로 층, 각층의 갯수, 들어갈 사람의 순서
		instream >> floor >> num >> cnt;
		int **ary = new int*[floor];
		for (int i = 0; i < floor; i++)
			ary[i] = new int[num]; // 층, 방갯수만큼 2차원 동적할당
		for (int i = 0; i < floor; i++) {
			for (int j = 0; j < num; j++) {
				ary[i][j] = (i + 1) * 100 + (j + 1);
			}
		}
		// 층부터 채우는것이므로 cnt를 floor만큼 나눌수 있을 때 까지 나눠서 방번호를 구한다.
		bool flag = false; // 각 층의 꼭대기 인 경우 초기값은 false
		int row, col;
		if (cnt % floor == 0)
			flag = true; // 꼭대기임이 참
		if (!flag) {
			row = cnt / floor; // 가로로 방번호 
			col = cnt % floor - 1; // 세로로 방의층 -1한 이유는 배열에서 구하기위해
		}
		else { // 꼭대기에 방이 있을 때
			row = cnt / floor - 1; // 가로로 방번호
			col = floor - 1; // 세로로 방번호
		}
		cout << ary[col][row] << endl;
		delete[]ary;
	}
	return 0;
}