#include <iostream>
#include <string>
using namespace std;

class Array {
public:
	int arr_size = 10000;
	int* arr;

	Array() {
		this->arr = new int[arr_size];
		for (int i = 0; i < arr_size; i++) {
			arr[i] = 0;
		}
	}

	void at(int idx) {
		if (arr[idx] == 0)
			cout << "0" << endl;
		else
			cout << arr[idx] << endl;
	}

	void set(int idx, int value) {
		if (arr[idx] == 0)
			cout << "0" << endl;
		else
			arr[idx] = value;
	}
	
	void add(int idx, int value) {
		if (arr[idx] == 0) {
			for (int i = 0; i <= idx; i++) {
				if (arr[i] == 0) {
					arr[i] = value;
					break;
				}
			}
		}
		else {
			for (int i = (arr_size-1); i >= idx; i--) {
				arr[i] = arr[i-1];
			}
			arr[idx] = value;
		}
	}

};

int main() {
	int num;
	string command;
	Array array;

	cin >> num;

	for (int i = 0; i < num; i++) {
		cin >> command;

		if (command == "at") {
			int N;
			cin >> N;
			array.at(N);
		}
		else if (command == "set") {
			int N, M;
			cin >> N >> M;
			array.set(N, M);
		}
		else if (command == "add") {
			int N, M;
			cin >> N >> M;
			array.add(N, M);
		}

	}

	return 0;
}