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

	int cases, teamNum, playNum;
	
	instream >> cases;
	for (int i = 0; i < cases; i++) {
		instream >> teamNum >> playNum; // 팀의갯수, 경기수
		int *teamNameGet = new int[teamNum + 1]; // 얻은점수 (팀의갯수만큼 동적할당받음 +1 해준이유는 팀이름이 1부터 시작하므로 헷갈리지 않게 아예 [0]은 빼고시작)
		int *teamNameLose = new int[teamNum + 1]; // 잃은 점수
		int *W = new int[teamNum + 1]; // 구할 기대값 W
		for (int z = 1; z < teamNum + 1; z++) { // 모두 0점으로 초기화
			teamNameGet[z] = 0;
			teamNameLose[z] = 0;
			W[z] = 0;
		}
		int a, b, p, q; // a,b는 팀 이름 p는 a가 낸 득점 q는 b가 낸 득점
		for (int j = 0; j < playNum; j++) {
			instream >> a >> b >> p >> q;
			for (int k = 1; k <= teamNum; k++) { // 이제 각 팀마다의 얻은점수, 잃은점수를 구한다
				if (a == k) { // 각 팀에 맞는 정보가 나오면
					teamNameGet[a] += p; // 얻은점수를 더하고
					teamNameLose[b] += p; // 잃은 점수를 더한다
					//break;
				}
				else if (b == k) {
					teamNameGet[b] += q;
					teamNameLose[a] += q;
					//break;
				}
			}
		}
		

		// 이제 얻은점수 잃은 점수를 토대로 기대값 W를 구한다
		for (int j = 1; j <= teamNum; j++) 
			W[j] = (teamNameGet[j] * teamNameGet[j]) * 1000 / ((teamNameGet[j] * teamNameGet[j]) + (teamNameLose[j] * teamNameLose[j]));

		
		// 이제 최대값, 최소값을 구한다
		int max = W[1];
		int min = W[1];
		for (int j = 2; j <= teamNum; j++) {
			if (max < W[j])
				max = W[j];
			else if (min > W[j])
				min = W[j];
		}
		cout << max << endl << min;
		cout << endl;

		for (int z = 1; z < teamNum + 1; z++) { // 모두 0점으로 초기화
			teamNameGet[z] = 0;
			teamNameLose[z] = 0;
			W[z] = 0;
		}
	}
	return 0;
}