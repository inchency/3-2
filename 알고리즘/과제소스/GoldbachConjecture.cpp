#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class Sum {
private:
	int a, b;
	int distract; // a-b의 값
public:
	void setA(int A) {
		a = A;
	}
	void setB(int B) {
		b = B;
	}
	void setDistract(int D) {
		distract = D;
	}
	int getA() {
		return a;
	}
	int getB() {
		return b;
	}
	int getDistract() {
		return distract;
	}
};

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt를 열 수 없습니다." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int numCases = 0; numCases < cases; numCases++) {
		int num;
		instream >> num;
		int cnt = 0; // 소수의 갯수
		for (int sosu = 2; sosu <= num; sosu++) { // num까지 중에 소수 찾기 (소수는 2부터임)
			if (sosu == 2) // 2는 항상 소수이므로
				cnt++;
			else { // 여기서 sosu가 진짜 소수인지 확인해준다
				for (int divide = 2; divide <= sosu; divide++) { // 여기서 divide는 나누는 수
					if ((sosu % divide == 0) && (divide != sosu))  // 나눠서 나머지가 0이란 뜻은 소수가 아니라는 뜻 단 나누는수가 sosu와 같을때는 제외
						break; // 더이상 검사할 필요가 없음
					else {
						if (divide == sosu) // divide == sosu 란 말은 즉슨 sosu는 진짜 소수이다.
							cnt++;
					}
				}
			}
		}
		int *sosuAry = new int[cnt]; // 소수의 갯수 cnt만큼 크기를 동적할당 해준다.
		for (int sosu = 2, i = 0; sosu <= num; sosu++) { // num까지 중에 소수 찾기 (소수는 2부터임)
			if (sosu == 2) // 2는 항상 소수이므로
				sosuAry[i++] = sosu;
			else { // 여기서 sosu가 진짜 소수인지 확인해준다
				for (int divide = 2; divide <= sosu; divide++) { // 여기서 divide는 나누는 수
					if ((sosu % divide == 0) && (divide != sosu))  // 나눠서 나머지가 0이란 뜻은 소수가 아니라는 뜻 단 나누는수가 sosu와 같을때는 제외
						break; // 더이상 검사할 필요가 없음
					else {
						if (divide == sosu) // divide == sosu 란 말은 즉슨 sosu는 진짜 소수이다.
							sosuAry[i++] = sosu;
					}
				}
			}
		}
		// 여기까지 num 까지 소수 찾기 완료 이제 소수의 합이 num 값인것을 찾아야함
		int count = 0; // 두 소수의 합이 num이 되는 갯수
		for (int i = 0; i < cnt - 1; i++) {
			for (int j = i; j < cnt; j++) {
				if (sosuAry[i] + sosuAry[j] == num)
					count++;
			}
		}
		Sum *sum = new Sum[count]; // count 갯수만큼 sumAry 동적할당
		for (int i = 0, k = 0; i < cnt; i++) {
			for (int j = i; j < cnt; j++) {
				if (sosuAry[i] + sosuAry[j] == num) {
					sum[k].setA(sosuAry[i]);
					sum[k++].setB(sosuAry[j]);
				}
			}
		}
		//여기까지 소수의합 되는거 다 찾음 이제 최소값이 되는것을 찾아야함
		for (int i = 0; i < count; i++)
			sum[i].setDistract(abs(sum[i].getA() - sum[i].getB()));
		//사실 배열에 자동으로 절대값의 차가 작은 것부터 저장되어 맨 마지막에 있는 것을 출력하면 되지만 어렵지 않으니 최소값을 찾아보도록 하겠다.
		int min = sum[0].getDistract();
		int store = 0;
		for (int i = 1; i < count; i++) {
			if (min > sum[i].getDistract()) {
				min = sum[i].getDistract();
				store = i;
			}
		}
		cout << sum[store].getA() << " " << sum[store].getB();
		cout << endl;
	}
	return 0;
}