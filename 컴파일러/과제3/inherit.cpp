class List {
	Cell *rear;
public:
	int empty() { 
	return rear = rear->next;
	}
	List() { rear = new Cell(0); }
protected:
	void add(int);
	void push(int);
	int get();
}

class Queue: public List {
public:
	Queue() { }
	int get(){ 
		return List::get();
	}

	void put(int x){ 
		add(x);
	}
}

Class Stack:private List{
public:
	Stack() { }
	int pop(){ 
		return get(); 
	}
	void push(int x){ 
		List::push(x); 
	}
	List::empty;
}
