#include <iostream>
#include <fstream>

using namespace std;

int gcd(int a, int b) {
	if (b == 0)
		return a;
	else // 문제에서 음수는 없다고 했으므로 그냥 else 해도 무방
		return gcd(b, a%b);
}

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
		int a, b;
		instream >> a >> b;
		cout << gcd(a, b);
		cout << endl;
	}
	return 0;
}