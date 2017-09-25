#include <iostream>
#include <fstream>

using namespace std;

int gcd(int a, int b) {
	if (b == 0)
		return a;
	else // �������� ������ ���ٰ� �����Ƿ� �׳� else �ص� ����
		return gcd(b, a%b);
}

int main() {
	ifstream instream;
	instream.open("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt�� �� �� �����ϴ�." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int testCases = 0; testCases < cases; testCases++) {
		int a, b;
		instream >> a >> b;
		cout << gcd(a, b);
		cout << endl;
	}
	return 0;
}