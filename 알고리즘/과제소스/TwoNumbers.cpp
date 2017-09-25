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
		cout << "input.txt�� �� �� �����ϴ�." << endl;
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
	int start, end, cnt, result, store; // start�� ���۰�, end�� ����, cnt�� ����, result�� ��갪, store�� ���� �ٻ��Ѱ� ���尪
	bool flag = false; // flag�� �Ǻ����� (target���̶� ��ġ�Ҷ� ī��Ʈ���ֱ�����)
	start = 0;
	end = num - 1;
	cnt = 1;
	store = NULL;
	while (start < end) {
		result = target - (ary[start] + ary[end]);
		if (result == 0) { // ��ġ�ϴ� ���� ������ start++, end--
			if (!flag) { // 0�ΰ� ã�Ҵµ� ó���� ��
				flag = true;
				cnt = 1;
			}
			else // 0�ΰ� ã�Ҵµ� ó���� �ƴ� ��
				cnt++;
			store = result; // store�� 0���� ����
			start++;
			end--;
		}
		else if (result < 0) { // �����̸� end--
			if (start == 0 && end == num - 1) // ù �����̸�
				store = abs(result);
			else { // ù ������ �ƴϸ�
				if (store >= abs(result)) {
					if (store == abs(result))  // ���ؼ� ������
						cnt++;
					else { // ���ؼ� store���� �� �������
						store = abs(result); // store ���Ҵ�
						cnt = 1;
					}
				}
			}
			end--;
		}
		else { // ����̸� start++
			if (start == 0 && end == num - 1) // ù �����̸�
				store = abs(result);
			else { // ù ������ �ƴϸ�
				if (store >= abs(result)) {
					if (store == abs(result)) // ���ؼ� ������
						cnt++;
					else { // ���ؼ� store���� �� �������
						store = abs(result); // store ���Ҵ�
						cnt = 1;
					}
				}
			}
			start++;
		}
	}
	return cnt;
}