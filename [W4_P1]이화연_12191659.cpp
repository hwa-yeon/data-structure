#include <iostream>
#include <string>
using namespace std;

class Node {
public:
	Node(int data);
	int data;
	Node* next;
	
};
Node::Node(int data) {
	this->data = data;
	this->next = NULL;
}

class LinkedList {
public:
	Node* f;
	Node* r;
	LinkedList();
	int front();
	int end();
	void addEnd(int data);
	int removeFront();
};
LinkedList::LinkedList() {
	this->f = NULL;
	this->r = NULL;
}
int LinkedList::front() {
	return f->data;
}
int LinkedList::end() {
	return r->data;
}
void LinkedList::addEnd(int data) {
	Node* newNode = new Node(data);
	if (f == NULL) {
		f = r = newNode;
	}
	else {
		r->next = newNode;
		r = newNode;
	}
}
int LinkedList::removeFront() {
	if (f != NULL) {
		Node* tmp = f;
		cout << f->data << endl;
		int tmp_int = f->data;
		f = f->next;
		delete tmp;
		return tmp_int;
	}
	return -1;
}

class LinkedQueue {
public:
	LinkedList *S;
	int capacity;
	int n;
	LinkedQueue(int cap);
	int size();
	int isEmpty();
	void front();
	void rear();
	void enqueue(int e);
	void dequeue();
};
LinkedQueue::LinkedQueue(int cap) {
	this->capacity = cap;
	this->S = new  LinkedList();
	this->n = 0;
}
int LinkedQueue::size() {
	return n;
}
int LinkedQueue::isEmpty() {
	if (n == 0) return 1;
	else return 0;
}
void LinkedQueue::front() {
	if (isEmpty() == true) {
		cout << "Empty" << endl;
	}
	else cout << S->front() << endl;
}
void LinkedQueue::rear() {
	if (isEmpty() == true) {
		cout << "Empty" << endl;
	}
	else cout << S->end() << endl;
}
void LinkedQueue::enqueue(int e) {
	if (n < capacity) {
		n++;
		S->addEnd(e);
	}
	else cout << "Full" << endl;
}
void LinkedQueue::dequeue() {
	if (isEmpty() == true) cout << "Empty" << endl;
	else {
		S->removeFront();
		n--;
	}
}

int main() {
	int capacity;
	int N;
	string command;

	cin >> capacity;
	cin >> N;

	LinkedQueue Q(capacity);

	for (int i = 0; i < N; i++) {
		cin >> command;

		if (command == "enqueue") {
			int input;
			cin >> input;
			Q.enqueue(input);
		}
		else if (command == "dequeue") {
			Q.dequeue();
		}
		else if (command == "size") {
			cout << Q.size() << endl;
		}
		else if (command == "isEmpty") {
			cout << Q.isEmpty() << endl;
		}
		else if (command == "front") {
			Q.front();
		}
		else if (command == "rear") {
			Q.rear();
		}
	}

	return 0;
}