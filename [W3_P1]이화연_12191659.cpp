#include <iostream>
#include <string>
using namespace std;

class Array_Stack {
public:
	int* Stack;
	int capacity;
	int t;

	Array_Stack(int capacity) {
		this->capacity = capacity;
		this->Stack = new int[capacity];
		this->t = -1;
	}

	int size() {
		return t + 1;
	}

	bool empty() {
		return t == -1;
	}

	int top() {
		if (empty()) return -1;
		else return Stack[t];
	}

	void push(int e) {
		if (size() == capacity) cout << "Full" << endl;
		else Stack[++t] = e;
	}

	int pop() {
		if (empty()) return -1;
		return Stack[t--];
	}
};


int main() {
	Array_Stack stack = Array_Stack(10000);
	int num;
	string command;

	cin >> num;
		
	for (int i = 0; i < num; i++) {
		cin >> command;

		if (command == "size") {
			cout << stack.size() << endl;
		}
		else if (command == "empty") {
			cout << stack.empty() << endl;;
		}
		else if (command == "top") {
			cout << stack.top() << endl;;
		}
		else if (command == "push") {
			int element;
			cin >> element;
			stack.push(element);
		}
		else if (command == "pop") {
			cout << stack.pop() << endl;
		}
	}

	return 0;
}