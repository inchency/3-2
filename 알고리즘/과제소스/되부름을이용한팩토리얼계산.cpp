#include <iostream>
#include <fstream>

using namespace std;

int recursiveFactorial(int n);

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
		cout << recursiveFactorial(num) << endl;
	}
	return 0;
}

int recursiveFactorial(int n) {
	if (n <= 1) //0! , 1! = 1
		return 1;
	else {
		return n * recursiveFactorial(n - 1);
	}
}
