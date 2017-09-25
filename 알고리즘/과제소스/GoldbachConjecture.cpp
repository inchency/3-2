#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class Sum {
private:
	int a, b;
	int distract; // a-b�� ��
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
		cout << "input.txt�� �� �� �����ϴ�." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int numCases = 0; numCases < cases; numCases++) {
		int num;
		instream >> num;
		int cnt = 0; // �Ҽ��� ����
		for (int sosu = 2; sosu <= num; sosu++) { // num���� �߿� �Ҽ� ã�� (�Ҽ��� 2������)
			if (sosu == 2) // 2�� �׻� �Ҽ��̹Ƿ�
				cnt++;
			else { // ���⼭ sosu�� ��¥ �Ҽ����� Ȯ�����ش�
				for (int divide = 2; divide <= sosu; divide++) { // ���⼭ divide�� ������ ��
					if ((sosu % divide == 0) && (divide != sosu))  // ������ �������� 0�̶� ���� �Ҽ��� �ƴ϶�� �� �� �����¼��� sosu�� �������� ����
						break; // ���̻� �˻��� �ʿ䰡 ����
					else {
						if (divide == sosu) // divide == sosu �� ���� �ｼ sosu�� ��¥ �Ҽ��̴�.
							cnt++;
					}
				}
			}
		}
		int *sosuAry = new int[cnt]; // �Ҽ��� ���� cnt��ŭ ũ�⸦ �����Ҵ� ���ش�.
		for (int sosu = 2, i = 0; sosu <= num; sosu++) { // num���� �߿� �Ҽ� ã�� (�Ҽ��� 2������)
			if (sosu == 2) // 2�� �׻� �Ҽ��̹Ƿ�
				sosuAry[i++] = sosu;
			else { // ���⼭ sosu�� ��¥ �Ҽ����� Ȯ�����ش�
				for (int divide = 2; divide <= sosu; divide++) { // ���⼭ divide�� ������ ��
					if ((sosu % divide == 0) && (divide != sosu))  // ������ �������� 0�̶� ���� �Ҽ��� �ƴ϶�� �� �� �����¼��� sosu�� �������� ����
						break; // ���̻� �˻��� �ʿ䰡 ����
					else {
						if (divide == sosu) // divide == sosu �� ���� �ｼ sosu�� ��¥ �Ҽ��̴�.
							sosuAry[i++] = sosu;
					}
				}
			}
		}
		// ������� num ���� �Ҽ� ã�� �Ϸ� ���� �Ҽ��� ���� num ���ΰ��� ã�ƾ���
		int count = 0; // �� �Ҽ��� ���� num�� �Ǵ� ����
		for (int i = 0; i < cnt - 1; i++) {
			for (int j = i; j < cnt; j++) {
				if (sosuAry[i] + sosuAry[j] == num)
					count++;
			}
		}
		Sum *sum = new Sum[count]; // count ������ŭ sumAry �����Ҵ�
		for (int i = 0, k = 0; i < cnt; i++) {
			for (int j = i; j < cnt; j++) {
				if (sosuAry[i] + sosuAry[j] == num) {
					sum[k].setA(sosuAry[i]);
					sum[k++].setB(sosuAry[j]);
				}
			}
		}
		//������� �Ҽ����� �Ǵ°� �� ã�� ���� �ּҰ��� �Ǵ°��� ã�ƾ���
		for (int i = 0; i < count; i++)
			sum[i].setDistract(abs(sum[i].getA() - sum[i].getB()));
		//��� �迭�� �ڵ����� ���밪�� ���� ���� �ͺ��� ����Ǿ� �� �������� �ִ� ���� ����ϸ� ������ ����� ������ �ּҰ��� ã�ƺ����� �ϰڴ�.
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