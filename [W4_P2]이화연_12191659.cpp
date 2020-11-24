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
		// cout << f->data << endl;
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
	int n;
	LinkedQueue();
	int size();
	int isEmpty();
	int front();
	int rear();
	void enqueue(int e);
	void dequeue();
};
LinkedQueue::LinkedQueue() {
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
int LinkedQueue::front() {
	if (isEmpty() == true) {
		cout << "Empty" << endl;
		return -1;
	}
	return S->front();
}
int LinkedQueue::rear() {
	if (isEmpty() == true) {
		cout << "Empty" << endl;
		return -1;
	}
	return S->end();
}
void LinkedQueue::enqueue(int e) {
	n++;
	S->addEnd(e);
}
void LinkedQueue::dequeue() {
	if (isEmpty() == true) cout << "Empty" << endl;
	else {
		S->removeFront();
		n--;
	}
}

class Card {
public:
	LinkedQueue person1, person2;
	int score1 = 0, score2 = 0;
	int capacity;
	Card();
	void setPerson(LinkedQueue person1, LinkedQueue person2);
	void setCapacity(int capacity);
	int battle();
};
Card::Card() {}
void Card::setPerson(LinkedQueue person1, LinkedQueue person2) {
	this->person1 = person1;
	this->person2 = person2;
}
void Card::setCapacity(int capacity) {
	this->capacity = capacity;
}
int Card::battle() {
	for (int i = 0; i < capacity; i++) {
		if (person1.S->f->data > person2.S->f->data) {
			score1++;
			int difference = (person1.S->f->data) - (person2.S->f->data);
			person1.dequeue();
			person2.dequeue();
			if (!person1.isEmpty()) {
				person1.S->f->data += (difference - 1);
			}
		}
		else if (person1.S->f->data < person2.S->f->data) {
			score2++;
			int difference = (person2.S->f->data) - (person1.S->f->data);
			person1.dequeue();
			person2.dequeue();
			if (!person2.isEmpty()) {
				person2.S->f->data += (difference - 1);
			}
		}
		else {
			person1.dequeue();
			person2.dequeue();
		}
	}

	if (score1 > score2)  return 1;
	else if (score1 < score2)  return 2;
	else return 0;
}

int main() {
	int test;
	int num;

	cin >> test;
	Card* card = new Card[test];
	LinkedQueue* person1 = new LinkedQueue[test];
	LinkedQueue* person2 = new LinkedQueue[test];

	for (int i = 0; i < test; i++) {
		cin >> num;
		for (int j = 0; j < num; j++) {
			int deck;
			cin >> deck;
			person1[i].enqueue(deck);
		}
		for (int j = 0; j < num; j++) {
			int deck;
			cin >> deck;
			person2[i].enqueue(deck);
		}
		card[i].setPerson(person1[i], person2[i]);
		card[i].setCapacity(num);
		cout << card[i].battle() << endl;
	}
	delete[] person1;
	delete[] person2;
	delete[] card;

	return 0;
}