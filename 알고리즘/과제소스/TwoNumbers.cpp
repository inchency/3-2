#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;

bool ascAry(int a, int b);
int count(int *ary, int num, int target);

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt를 열 수 없습니다." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int testCases = 0; testCases < cases; testCases++) {
		int num, target;
		instream >> num >> target;
		int *ary = new int[num];
		for (int i = 0; i < num; i++)
			instream >> ary[i];
		sort(ary, ary + num, ascAry);
		cout << count(ary, num, target) << endl;
		delete[] ary;
	}
	return 0;
}

bool ascAry(int a, int b) {
	return a < b;
}

int count(int *ary, int num, int target) {
	int start, end, cnt, result, store; // start는 시작값, end는 끝값, cnt는 갯수, result은 계산값, store은 가장 근사한값 저장값
	bool flag = false; // flag는 판별변수 (target값이랑 일치할때 카운트해주기위함)
	start = 0;
	end = num - 1;
	cnt = 1;
	store = NULL;
	while (start < end) {
		result = target - (ary[start] + ary[end]);
		if (result == 0) { // 일치하는 값이 있으면 start++, end--
			if (!flag) { // 0인걸 찾았는데 처음일 때
				flag = true;
				cnt = 1;
			}
			else // 0인걸 찾았는데 처음이 아닐 때
				cnt++;
			store = result; // store은 0으로 저장
			start++;
			end--;
		}
		else if (result < 0) { // 음수이면 end--
			if (start == 0 && end == num - 1) // 첫 시작이면
				store = abs(result);
			else { // 첫 시작이 아니면
				if (store >= abs(result)) {
					if (store == abs(result))  // 비교해서 같으면
						cnt++;
					else { // 비교해서 store보다 더 작은경우
						store = abs(result); // store 재할당
						cnt = 1;
					}
				}
			}
			end--;
		}
		else { // 양수이면 start++
			if (start == 0 && end == num - 1) // 첫 시작이면
				store = abs(result);
			else { // 첫 시작이 아니면
				if (store >= abs(result)) {
					if (store == abs(result)) // 비교해서 같으면
						cnt++;
					else { // 비교해서 store보다 더 작은경우
						store = abs(result); // store 재할당
						cnt = 1;
					}
				}
			}
			start++;
		}
	}
	return cnt;
}