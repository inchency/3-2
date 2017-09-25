#include <iostream>
#include <fstream>
#include <cstring>
//#include "Stack.h"
#define MAX_SIZE 50
using namespace std;

class Stack {
public:
private:
	int *arrayOfData;
	int top;
	const int size;
public:
	Stack(int size);
	virtual~Stack();
	bool isFull() const;
	bool isEmpty() const;
	void push(int value);
	int pop();
	void print() const;
};

Stack stack1(MAX_SIZE); // ( 담는 스택
Stack stack2(MAX_SIZE); // ) 담는 스택

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt를 열 수 없습니다." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	char buffer[MAX_SIZE];
	instream.getline(buffer, 80);
	for (int numCases = 0; numCases < cases; numCases++) { // 한줄씩 읽고 최대 80바이트까지 읽어서 buffer에 넣음
		instream.getline(buffer, 80);
		int len = strlen(buffer);
		//for (int k = 0; k < len; k++) 
		//cout << buffer[k];
		//cout << endl;
		if (buffer[0] == ')' || buffer[len - 1] == '(')
			cout << "NO" << endl;
		else {
			int i = 0, j = 0;
			for (int k = 0; k < len; k++) {
				if (buffer[k] == '(') { // '('이면 stack1에 저장
					stack1.push(buffer[k]);
					i++;
				}
				else { // ')'이면 stack2에 저장
					stack2.push(buffer[k]);
					j++;
				}
			}
			if (i != j) // (와 )의 갯수가 같으면
				cout << "NO" << endl;
			else
				cout << "YES" << endl;
			//사실 갯수만 세주면 되지만 스택을 한번 써보고싶어서 이렇게 구현해 보았음
			//stack1.print();
			//stack2.print();
			//cout << endl << endl;
			stack1.~Stack();
			stack2.~Stack();
		}
	}

	return 0;
}

Stack::Stack(int size) :size(size) { // 데이터 초기화
	arrayOfData = new int[size];
	top = -1;
}

Stack::~Stack() {
	while (isEmpty() == false)
		pop();
}

bool Stack::isFull() const {
	if (top == size - 1)
		return true;
	else
		return false;
}

bool Stack::isEmpty() const {
	if (top == -1)
		return true;
	else
		return false;
}

void Stack::push(int value) {
	if (isFull() == true)
		cout << "Stack is Full" << endl;
	else {
		++top;
		arrayOfData[top] = value;
	}
}

int Stack::pop() {
	if (isEmpty() == true)
		cout << "Stack is Empty" << endl;
	else
		return arrayOfData[top--];
}

void Stack::print() const {
	if (isEmpty() == true)
		cout << "Stack is Empty" << endl;
	for (int i = 0; i <= top; i++) {
		cout << arrayOfData[i] << " ";
	}
	cout << endl;
}