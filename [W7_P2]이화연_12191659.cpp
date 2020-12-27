#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
	int data;
	Node* par;
	vector<Node*> chi_v;

	Node(int data) {
		this->data = data;
		this->par = NULL;
	}
	~Node() {}

	void setParent(Node* parent) {
		this->par = parent;
	}
	void insertChild(Node* child) {
		this->chi_v.push_back(child);
	}
	void deleteChild(Node* child) {
		for (int i = 0; i < this->chi_v.size(); i++) {
			if (this->chi_v[i] == child) {
				this->chi_v.erase(this->chi_v.begin() + i);
			}
		}
	}
};

class Tree {
public:
	Node* root;
	int number = 0;
	vector<Node*> node_list;

	Tree(int);
	~Tree() {};
	int size();
	void insertNode(int, int);
	void preorder(Node*);
	void postorder(Node*);
};

Tree::Tree(int data) {
	Node* node = new Node(data);
	root = node;
	node_list.push_back(node);
}
int Tree::size() {
	return node_list.size();
}
void Tree::insertNode(int par_data, int data) {
	for (int i = 0; i < size(); i++) {
		if (node_list[i]->data == par_data) {
			Node* node = new Node(data);
			node->setParent(node_list[i]);
			node_list[i]->insertChild(node);
			node_list.push_back(node);
			return;
		}
	}
}
void Tree::preorder(Node* node) {
	if (!node)  return;

	// cout << node->data << " ";
	number++;
	for (int i = 0; i < node->chi_v.size(); i++) {
		preorder(node->chi_v[i]);
	}

	if(number != 0)	 cout << number << " ";
	number = 0;
}
void Tree::postorder(Node* node) {
	if (!node)	return;

	for (int i = 0; i < node->chi_v.size(); i++) {
		postorder(node->chi_v[i]);
	}
	// cout << node->data << " ";
}

int main() {
	int n, m;
	int num1, num2;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> m;
		Tree t = Tree(1);
		for (int j = 0; j < m; j++) {
			cin >> num1 >> num2;
			t.insertNode(num1, num2);
		}
		t.preorder(t.root);
		cout << endl;
	}

	return 0;
}