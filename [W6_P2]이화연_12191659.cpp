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
	void delChild(Node* child) {
		for (int i = 0; i < this->chi_v.size(); i++) {
			if (this->chi_v[i] == child) {
				this->chi_v.erase(this->chi_v.begin() + i);
			}
		}
	}
};

class Tree {
private:
	Node* root;
	vector<Node*> node_list;
public:
	Tree(int);
	~Tree() {};
	int size();
	void insertNode(int, int);
	void delNode(int);
	void printChi(int);
	void printSib(int);
	int depth(int);
};
Tree::Tree(int data) {
	root = new Node(data);
	node_list.push_back(root);
}
int Tree::size() {
	int n = 0;
	for (int i = 0; i < node_list.size(); i++) {
		n++;
	}
	return n;
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
void Tree::delNode(int data) {
	Node* nownode;
	Node* par;
	for (int i = 0; i < this->node_list.size(); i++) {
		if (this->node_list[i]->data == data) {
			nownode = node_list[i];
			if (nownode == root) {
				return;
			}
			par = nownode->par;
			for (Node*& child : nownode->chi_v) {
				par->insertChild(child);
				child->par = par;
			}
			par->delChild(nownode);
			this->node_list.erase(this->node_list.begin() + i);
			delete nownode;
		}
	}
	return;
}
void Tree::printChi(int data) {
	for (int i = 0; i < size(); i++) {
		if (node_list[i]->data == data) {
			if (node_list[i]->chi_v.size() == 0) {
				cout << "0" << endl;
				return;
			}
			for (int j = 0; j < node_list[i]->chi_v.size(); j++) {
				cout << node_list[i]->chi_v[j]->data << " ";
			}
			cout << endl;
			return;
		}
	}
}
void Tree::printSib(int data) {
	for (int i = 0; i < size(); i++) {
		if (node_list[i]->data == data) {
			if (node_list[i]->par == NULL) cout << data << endl;
			else {
				Node* par_node = node_list[i]->par;
				for (int j = 0; j < par_node->chi_v.size(); j++) {
					cout << par_node->chi_v[j]->data << " ";
				}
				cout << endl;
				return;
			}
		}
	}
	cout << 0 << endl;
}
int Tree::depth(int data) {
	int number = 0;
	Node* nownode;

	for (int i = 0; i < size(); i++) {
		if (node_list[i]->data == data) {
			nownode = node_list[i];

			while (nownode->par != NULL) {
				// cout << nownode->data << " " << nownode->par->data << endl;
				number++;
				nownode = nownode->par;
			}
		}
	}
	return number;
}

int main() {
	int n, m;
	cin >> n >> m;
	Tree t = Tree(1);

	for (int i = 0; i < n; i++) {
		int par, data;
		cin >> par >> data;
		t.insertNode(par, data);
	}
	for (int i = 0; i < m; i++) {
		int data;
		cin >> data;
		cout << t.depth(data) << endl;
	}

	return 0;
}