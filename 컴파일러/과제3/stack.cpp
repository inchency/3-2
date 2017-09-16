class Stack {
public:
	char pop();
	void push(char);
		 Stack() { top = 0;}
private:
	int top;
	char elements[101];
}

char Stack::pop() {
	top = top -1;
	return elements[top+1];
}

char Stack::push(char c) {
	top = top +1;
	elements[top] = c;
}
