#include <iostream>
#include <fstream>

using namespace std;

int gcd(int a, int b); // �ִ����� �Լ� (�˰��� �ð��� ��� recursive �̿�)
int lcm(int a, int b); // �ּҰ���� �Լ�

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt�� �� �� �����ϴ�." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int numCases = 0; numCases < cases; numCases++) {
		int a, b; // a�� ���� b�� �и�
		instream >> a >> b;

		int i = 2;
		while (1) {
			int testA = a % gcd(a, b);
			int testB = b % gcd(a, b);
			int store_gcd = gcd(a, b);
			if (testA == 0 && testB == 0) { // ���м��� �ƴ϶�� ���м��� ���� ������ش�
				a = a / store_gcd;
				b = b / store_gcd;
			}
			if (a == 1) {
				cout << b << endl;
				break;
			}
			else {
				int l = lcm(b, i); // l�� b,i�� �ּҰ����
				int la = l / i; // la�� i�� ����
				int oa = l / b * a; // oa�� �������� ����
				if (la <= oa) { // la�� �� �������� ���� �м��� �����ϴٴ� ��
					a = oa - la;
					b = l;
				}
				i++;
			}
		}
	}
	return 0;
}

int gcd(int a, int b) { // �˰��� �ð��� ��� �����(recursive)�� �̿��Ͽ���.
	if (b == 0)
		return a;
	else
		return gcd(b, a%b);
}
int lcm(int a, int b) {
	int c = gcd(a, b); // c�� a��b�� �ִ�����
	return c*(a / c)*(b / c);
}