#include <iostream>
#include <string>
using namespace std;

class Node {
public:
	int data;
	Node* next;

	Node(int data) {
		this->data = data;
		this->next = NULL;
	}
};

class S_LinkedList {
public:
	Node* head;
	Node* tail;

	S_LinkedList() {
		head = NULL;
		tail = NULL;
	}

	void addFront(int value) {
		Node* new_node = new Node(value);
		new_node->next = head;
		head = new_node;
	}

	void removeFront() {
		if (head != NULL) {
			Node* cur_node = head;
			head = cur_node->next;
			cout << cur_node->data << endl;
			delete cur_node;
		}
		else
			cout << -1 << endl;
	}

	void front() {
		if (head != NULL)
			cout << head->data << endl;
		else
			cout << -1 << endl;
	}

	void empty() {
		if (head == NULL && tail == NULL) {
			cout << 1 << endl;
		}
		else
			cout << 0 << endl;
	}
};

int main() {
	int num;
	string command;
	S_LinkedList linkedlist;

	cin >> num;

	for (int i = 0; i < num; i++) {
		cin >> command;

		if (command == "addFront") {
			int N;
			cin >> N;
			linkedlist.addFront(N);
		}
		else if (command == "removeFront") {
			linkedlist.removeFront();
		}
		else if (command == "front") {
			linkedlist.front();
		}
		else if (command == "empty") {
			linkedlist.empty();
		}
		
	}

	return 0;
}