#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

class Stack {
public:
	char* stack;
	int capacity;
	int t;
	
	Stack(int capacity) {
		this->capacity = capacity;
		this->stack = new char[capacity];
		this->t = -1;
	}

	int size() {
		return t + 1;
	}

	bool empty() {
		return t == -1;
	}

	char top() {
		if (empty()) return 'Z';
		else return stack[t];
	}

	void push(char e) {
		if (size() == capacity) cout << "Full" << endl;
		else stack[++t] = e;
	}

	char pop() {
		if (empty()) return 'Z';
		return stack[t--];
	}
};
class calPostfix {
public:
	Stack stack = Stack(10000);
	string postfix;

	calPostfix(string exp) {
		postfix = exp;
	}

	bool isOper(char item) {
		if (item == '+' || item == '-' || item == '*') {
			return true;
		}
		else return false;
	}

	bool isNum(char item) {
		if (typeid(item - '0') == typeid(int)) {
			return true;
		}
		else return false;
	}

	int getOper_order(char op) {
		switch (op) {
		case '*':
			return 2;
		case '+':
			return 1;
		case '-':
			return 1;
		case '(':
			return 0;
		default:
			return -1;
		}
	}

	int compareOper(char op1, char op2) {
		int op1Prec = getOper_order(op1);
		int op2Prec = getOper_order(op2);

		if (op1Prec > op2Prec)
			return 1;
		else if (op1Prec < op2Prec)
			return -1;
		else
			return 0;
	}

	void printPostfix() {
		for (unsigned int i = 0; i < postfix.size(); i++) {
			char ch = postfix[i];

			if (isOper(ch)) {
				if (stack.empty()) {
					stack.push(ch);
				}
				else {
					while (compareOper(stack.top(), ch) != -1)
						cout << stack.pop();

					stack.push(ch);
				}
			}
			else if (ch == '(') {
				stack.push(postfix[i]);
			}

			else if (ch == ')') {
				while (!stack.empty() && stack.top() != '(') {
					cout << stack.pop();
				}
				stack.pop();
			}

			else if (isNum(ch)) {
				cout << ch;
			}

		}

		while (!stack.empty()) {
			cout << stack.pop();
		}
		cout << endl;
	}

};

int main() {
	int num;
	string math;

	cin >> num;

	for (int i = 0; i < num; i++) {
		cin >> math;
		calPostfix post = calPostfix(math);
		post.printPostfix();
	}

	return 0;
}