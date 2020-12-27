#include <iostream>
#include <string>
using namespace std;

#define MappingSize 501

class vertex {
public:
	vertex *prev;
	vertex *next;
	int degree;
	int data;
	vertex(int data) {
		this->degree = 0;
		this->data = data;
	}
	void increase_degree() {
		this->degree++;
	}
	void decrease_degree() {
		this->degree--;
	}
};

class edge {
public:
	edge* prev;
	edge* next;
	vertex* source;
	vertex* destination;
	string data;
	edge(vertex* a, vertex* b, string data) {
		this->source = a;
		this->destination = b;
		this->data = data;
	}
};

class DoublyVertexLinkedList {
public:
	vertex* head;
	vertex* tail;
	DoublyVertexLinkedList() {
		this->head = NULL;
		this->tail = NULL;
	}
	void insert(vertex* insertVertex) {
		if (this->head == NULL) {
			head = insertVertex;
			tail = insertVertex;
		}
		else {
			tail->next = insertVertex;
			insertVertex->prev = tail;
			tail = insertVertex;
		}
	}
	void remove(vertex* delVertex) {
		if (delVertex == head || delVertex == tail) {
			if (delVertex == head && delVertex != tail) {
				vertex* tmp = head;
				head = head->next;
				head->prev = NULL;
				delete tmp;
			}
			else if (delVertex == tail && delVertex != head) {
				vertex* tmp = tail;
				tail = tail->prev;
				tail->next = NULL;
				delete tmp;
			}
			else {
				head = NULL;
				tail = NULL;
			}
		}
		else {
			delVertex->prev->next = delVertex->next;
			delVertex->next->prev = delVertex->prev;
			delete delVertex;
		}
	}
};

class DoublyEdgeLinkedList {
public:
	edge* head;
	edge* tail;
	DoublyEdgeLinkedList() {
		this->head = NULL;
		this->tail = NULL;
	}
	void insert(edge* insertEdge) {
		if (this->head == NULL) {
			head = insertEdge;
			tail = insertEdge;
		}
		else {
			tail->next = insertEdge;
			insertEdge->prev = tail;
			tail = insertEdge;
		}
	}
	void remove(edge* delEdge) {
		if (delEdge == head || delEdge == tail) {
			if (delEdge == head && delEdge != tail) {
				edge* tmp = head;
				head = head->next;
				head->prev = NULL;
				delete tmp;
			}
			else if (delEdge == tail && delEdge != head) {
				edge* tmp = tail;
				tail = tail->prev;
				tail->next = NULL;
				delete tmp;
			}
			else {
				head = NULL;
				tail = NULL;
			}
		}
		else {
			delEdge->prev->next = delEdge->next;
			delEdge->next->prev = delEdge->prev;
			delete delEdge;
		}
	}
};

class graph {
public:
	edge*** edgeMatrix;
	DoublyVertexLinkedList* VertexList;
	DoublyEdgeLinkedList* EdgeList;
	int vertexSize;
	int edgeSize;
	int mappingTable[MappingSize];

	graph() {
		this->VertexList = new DoublyVertexLinkedList();
		this->EdgeList = new DoublyEdgeLinkedList();
		this->vertexSize = 0;
		this->edgeSize = 0;
		for (int i = 0; i < MappingSize; i++)
			mappingTable[i] = -1;
		this->edgeMatrix = new edge**[1];
		this->edgeMatrix[0] = new edge*[1];
		this->edgeMatrix[0][0] = NULL;
	}
	bool isfindVertex(int n) {
		bool flag = false;
		vertex* tmp = VertexList->head;
		while (tmp != NULL) {
			if (tmp->data == n) {
				flag = true;
				break;
			}
			tmp = tmp->next;
		}
		return flag;
	}
	vertex* findVertex(int n) {
		vertex* tmp = VertexList->head;
		while (tmp != NULL) {
			if (tmp->data == n) {
				break;
			}
			tmp = tmp->next;
		}
		return tmp;
	}
	void insert_vertex(int n) {
		if (isfindVertex(n) == true) {
			return;
		}
		else {
			edge*** tmpMatrix = new edge**[vertexSize + 1];
			for (int i = 0; i < vertexSize + 1; i++) {
				tmpMatrix[i] = new edge*[vertexSize + 1];
				for (int j = 0; j < vertexSize + 1; j++) {
					tmpMatrix[i][j] = NULL;
				}
			}
			for (int i = 0; i < vertexSize; i++) {
				for (int j = 0; j < vertexSize; j++) {
					tmpMatrix[i][j] = this->edgeMatrix[i][j];
				}
			}
			this->edgeMatrix = tmpMatrix;

			vertex* newVertex = new vertex(n);
			VertexList->insert(newVertex);
			this->vertexSize++;
			mappingTable[vertexSize - 1] = n;
		}
	}
	void erase_vertex(int n) {
		if (isfindVertex(n) == false || vertexSize == 0) {
			cout << -1 << endl;
			return;
		}
		else {
			edge*** tmpMatrix = new edge**[vertexSize - 1];
			for (int i = 0; i < vertexSize - 1; i++) {
				tmpMatrix[i] = new edge*[vertexSize - 1];
				for (int j = 0; j < vertexSize - 1; j++) {
					tmpMatrix[i][j] = NULL;
				}
			}

			int middleIdx = 0;
			for (int i = 0; i < vertexSize; i++) {
				if (mappingTable[i] == n)
					middleIdx = i;
			}
			for (int i = middleIdx; i < vertexSize; i++) {
				mappingTable[i] = mappingTable[i + 1];
			}
			for (int i = 0; i < vertexSize; i++) {
				if (this->edgeMatrix[middleIdx][i] != NULL) {
					// cout << this->edgeMatrix[middleIdx][i]->data << " ";
					EdgeList->remove(this->edgeMatrix[middleIdx][i]);
					this->edgeSize--;
				}
			}
			for (int i = 0; i < vertexSize; i++) {
				for (int j = 0; j < vertexSize; j++) {
					if (i < middleIdx && j < middleIdx) {
						tmpMatrix[i][j] = this->edgeMatrix[i][j];
					}
					else if (i > middleIdx && j > middleIdx) {
						tmpMatrix[i - 1][j - 1] = this->edgeMatrix[i][j];
					}
					else if (j > middleIdx) {
						tmpMatrix[i][j - 1] = this->edgeMatrix[i][j];
					}
					else if (i > middleIdx) {
						tmpMatrix[i - 1][j] = this->edgeMatrix[i][j];
					}
				}
			}
			this->edgeMatrix = tmpMatrix;
			VertexList->remove(findVertex(n));
			this->vertexSize--;

			cout << this->edgeSize << " ";
			edge* nowEdge = EdgeList->head;
			for (int i = 0; i < edgeSize; i++) {
				cout << nowEdge->data << " ";
				nowEdge = nowEdge->next;
			}
			cout << endl;
		}
	}
	void insert_edge(int indirectSource, int indirectDestination, string data) {
		if (isfindVertex(indirectSource) == false || isfindVertex(indirectDestination) == false) {
			cout << -1 << endl;
			return;
		}
		int destination = -1;
		int source = -1;
		for (int i = 0; i <= vertexSize; i++) {
			if (mappingTable[i] == indirectDestination)
				destination = i;
			if (mappingTable[i] == indirectSource)
				source = i;
			if (source != -1 && destination != -1)
				break;
		}
		if (edgeMatrix[source][destination] != NULL || edgeMatrix[destination][source] != NULL) {
			cout << -1 << endl;
			return;
		}

		edge* newEdge = new edge(findVertex(indirectSource), findVertex(indirectDestination), data);
		edgeMatrix[source][destination] = newEdge;
		edgeMatrix[destination][source] = newEdge;

		findVertex(indirectSource)->increase_degree();
		findVertex(indirectDestination)->increase_degree();

		EdgeList->insert(newEdge);
		this->edgeSize++;
	}
	void erase_edge(int indirectSource, int indirectDestination) {
		int destination = -1;
		int source = -1;
		for (int i = 0; i <= vertexSize; i++) {
			if (mappingTable[i] == indirectDestination)
				destination = i;
			if (mappingTable[i] == indirectSource)
				source = i;
			if (source != -1 && destination != -1)
				break;
		}
		if (edgeMatrix[source][destination] == NULL || edgeMatrix[destination][source] == NULL)
			return;
		findVertex(indirectSource)->decrease_degree();
		findVertex(indirectDestination)->decrease_degree();

		edge* delEdge = edgeMatrix[source][destination];
		EdgeList->remove(delEdge);

		edgeMatrix[source][destination] = NULL;
		edgeMatrix[destination][source] = NULL;
		this->edgeSize--;
	}
};

int main() {
	graph graph;
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		int o;
		cin >> o;
		graph.insert_vertex(o);
	}
	for (int i = 0; i < m; i++) {
		int s, d;
		string str;
		cin >> s >> d >> str;
		graph.insert_edge(s, d, str);
	}
	cout << graph.vertexSize << " " << graph.edgeSize << endl;
	for (int i = 0; i < k; i++) {
		int o;
		cin >> o;
		graph.erase_vertex(o);
	}

	return 0;
}