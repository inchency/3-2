#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream instream;
	instream.open("input.txt");

	if (!instream.is_open()) {
		cout << "input.txt�� �� �� �����ϴ�." << endl;
		return -1;
	}

	int cases, teamNum, playNum;
	
	instream >> cases;
	for (int i = 0; i < cases; i++) {
		instream >> teamNum >> playNum; // ���ǰ���, ����
		int *teamNameGet = new int[teamNum + 1]; // �������� (���ǰ�����ŭ �����Ҵ���� +1 ���������� ���̸��� 1���� �����ϹǷ� �򰥸��� �ʰ� �ƿ� [0]�� �������)
		int *teamNameLose = new int[teamNum + 1]; // ���� ����
		int *W = new int[teamNum + 1]; // ���� ��밪 W
		for (int z = 1; z < teamNum + 1; z++) { // ��� 0������ �ʱ�ȭ
			teamNameGet[z] = 0;
			teamNameLose[z] = 0;
			W[z] = 0;
		}
		int a, b, p, q; // a,b�� �� �̸� p�� a�� �� ���� q�� b�� �� ����
		for (int j = 0; j < playNum; j++) {
			instream >> a >> b >> p >> q;
			for (int k = 1; k <= teamNum; k++) { // ���� �� �������� ��������, ���������� ���Ѵ�
				if (a == k) { // �� ���� �´� ������ ������
					teamNameGet[a] += p; // ���������� ���ϰ�
					teamNameLose[b] += p; // ���� ������ ���Ѵ�
					//break;
				}
				else if (b == k) {
					teamNameGet[b] += q;
					teamNameLose[a] += q;
					//break;
				}
			}
		}
		

		// ���� �������� ���� ������ ���� ��밪 W�� ���Ѵ�
		for (int j = 1; j <= teamNum; j++) 
			W[j] = (teamNameGet[j] * teamNameGet[j]) * 1000 / ((teamNameGet[j] * teamNameGet[j]) + (teamNameLose[j] * teamNameLose[j]));

		
		// ���� �ִ밪, �ּҰ��� ���Ѵ�
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

		for (int z = 1; z < teamNum + 1; z++) { // ��� 0������ �ʱ�ȭ
			teamNameGet[z] = 0;
			teamNameLose[z] = 0;
			W[z] = 0;
		}
	}
	return 0;
}