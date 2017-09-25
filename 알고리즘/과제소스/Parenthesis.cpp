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

Stack stack1(MAX_SIZE); // ( ��� ����
Stack stack2(MAX_SIZE); // ) ��� ����

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt�� �� �� �����ϴ�." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	char buffer[MAX_SIZE];
	instream.getline(buffer, 80);
	for (int numCases = 0; numCases < cases; numCases++) { // ���پ� �а� �ִ� 80����Ʈ���� �о buffer�� ����
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
				if (buffer[k] == '(') { // '('�̸� stack1�� ����
					stack1.push(buffer[k]);
					i++;
				}
				else { // ')'�̸� stack2�� ����
					stack2.push(buffer[k]);
					j++;
				}
			}
			if (i != j) // (�� )�� ������ ������
				cout << "NO" << endl;
			else
				cout << "YES" << endl;
			//��� ������ ���ָ� ������ ������ �ѹ� �Ẹ��; �̷��� ������ ������
			//stack1.print();
			//stack2.print();
			//cout << endl << endl;
			stack1.~Stack();
			stack2.~Stack();
		}
	}

	return 0;
}

Stack::Stack(int size) :size(size) { // ������ �ʱ�ȭ
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