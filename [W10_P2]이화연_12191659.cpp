#include <iostream>
#include <string>
#include <vector>

using namespace std;
enum direction { MIN = 1, MAX = -1 };

int cnt = 0;

class Heap {
private:
	vector<int> v;
	int heap_size;
	int root_index;
	int direction;
public:
	Heap(int direction) {
		v.push_back(-1);
		this->heap_size = 0;
		this->root_index = 1;
		this->direction = direction;
	}
	void swap(int idx1, int idx2) {
		v[0] = v[idx1];
		v[idx1] = v[idx2];
		v[idx2] = v[0];
	}
	void unHeap(int idx) {
		cnt++;
		if (idx == root_index) return;
		else {
			int parent = idx / 2;
			if (v[parent] * direction > v[idx] * direction) {
				swap(parent, idx);
				unHeap(parent);
			}
		}
	}
	void downHeap(int idx) {
		int left = idx * 2;
		int right = idx * 2 + 1;
		if (right <= heap_size) {
			if (v[left] * direction <= v[right] * direction) {
				if (v[left] * direction < v[idx] * direction) {
					swap(left, idx);
					downHeap(left);
				}
				else return;
			}
			else {
				if (v[right] * direction < v[idx] * direction) {
					swap(right, idx);
					downHeap(right);
				}
				else return;
			}
		}
		else if (left <= heap_size) {
			if (v[left] * direction < v[idx] * direction) {
				swap(left, idx);
				downHeap(left);
			}
			else return;
		}
		else return;
	}
	void insert(int e) {
		v.push_back(e);
		heap_size++;
		unHeap(heap_size);
	}
	int pop() {
		if (isEmpty() == false) {
			int top = v[root_index];
			v[root_index] = v[heap_size];
			heap_size--;
			v.pop_back();
			downHeap(root_index);
			return top;
		}
		else
			return -1;
	}
	int top() {
		if (isEmpty() == false)
			return v[root_index];
		else
			return -1;
	}
	int size() {
		return heap_size;
	}
	bool isEmpty() {
		if (heap_size == 0) return true;
		else return false;
	}
	void print() {
		if (isEmpty() == false) {
			for (int i = root_index; i < heap_size; i++) {
				cout << v[i] << " ";
			}
			cout << v[heap_size] << endl;
		}
		else cout << -1 << endl;
	}
	int find(int x) {
		if (isEmpty() == false) return v.at(x);
	}
	int findnum(int x) {
		if (isEmpty() == false) {
			vector<int> newv;
			newv = v;
			for (int i = root_index; i < newv.size(); i++) {
				for (int j = root_index + 1; j < newv.size(); j++) {
					if (newv[j - 1] > newv[j]) {
						int number = newv[j - 1];
						newv[j - 1] = newv[j];
						newv[j] = number;
					}
				}
			}
			return newv.at(x);
		}
	}
};

int main() {
	int num;
	cin >> num;

	for (int i = 0; i < num; i++) {
		Heap PQ(MIN);
		int n, m;
		cin >> n >> m;
		for (int j = 0; j < n; j++) {
			int in;
			cin >> in;
			PQ.insert(in);
		}
		PQ.print();
		cout << PQ.find(m) << endl;
		cout << PQ.findnum(m) << endl;
		cout << cnt << endl;
	}
	return 0;
}