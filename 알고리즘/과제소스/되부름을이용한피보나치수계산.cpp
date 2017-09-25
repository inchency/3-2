#include <iostream>
#include <fstream>

using namespace std;

int recursiveFibo(int n);

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt를 열 수 없습니다" << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int testCases = 0; testCases < cases; testCases++) {
		int num;
		instream >> num;
		cout << recursiveFibo(num) << endl;
	}
	return 0;
}

int recursiveFibo(int n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return recursiveFibo(n - 2) + recursiveFibo(n - 1);
}