#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node {
	public:
	int root; //1 if root, 0 if not
	int id;
	int freq;
	Node* left;
	Node* right;
	Node();
	~Node();
	Node (int check, int ident, int frequency);
};

Node::Node(){
};

Node::Node(int check, int ident, int frequency) {
	root = check;
	id = ident;
	freq = frequency;
	left = NULL;
	right = NULL;
}

struct comp : public binary_function<Node*, Node*, bool> {
	bool operator() (const Node* l, const Node* r) const{
		return (l->freq > r->freq);
	}
};

void print(Node* input, string code, int id) {
	//cout << "debug1" << endl;
	if (input == NULL) {
		//cout << "debug2" << endl;
		return;
	}
	else if (input->root != 1 && id == input->id) {
		//cout << "debug3" << endl;
		cout << code << endl;
	}
	//cout << "debug6" << endl;
	print(input->left, code+"0", id);
	//cout << "debug4" << endl;
	print(input->right, code+"1", id);
	//cout << "debug5" << endl;
}

void Huffman (int id[], int freq[], int size) {
	Node* left = new Node;
	Node* right = new Node;
	Node* root = new Node;
	Node* temp = new Node;
	int newID;
	priority_queue<Node*, vector<Node*>, comp> minHeap;
	for (int i = 0; i < size; i++) {
		minHeap.push(new Node(0, id[i], freq[i]));
	}
	while (minHeap.size() != 1) {
		left = minHeap.top();
		minHeap.pop();
		right = minHeap.top();
		minHeap.pop();
		newID = left->id;
		if (left->freq == right->freq) {
			if (right->id < left->id) {
				temp = right;
				right = left;
				left = temp;
				newID = right->id;
			}
		}
		root = new Node(1, newID, left->freq+right->freq);
		root->left = left;
		root->right = right;
		minHeap.push(root);
	}
	for (int i = 0; i < size; i++) {
		print(minHeap.top(), "", id[i]);
	}
}

int main() {
	int size;
	cin >> size;
	int freq[size];
	int id[size];
	for (int i = 0; i < size; i++) {
		cin >> freq[i];
		id[i] = i;
	}
	Huffman(id, freq, size);
}
