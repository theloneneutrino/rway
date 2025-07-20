#ifndef RWAYTRIE_H
#define RWAYTRIE_H

#include <string>

using namespace std;

struct Node {
public:
	static const int SIZE_OF_NODE_ARRAY = 256;  // Moved to public
	int value;
	Node* next[SIZE_OF_NODE_ARRAY];
	Node();
};

class RWayTrie {
	Node* root;
	Node* get(Node* x, const string& key, int d);
	Node* insert(Node* x, const string& key, int val, int d);
public:
	RWayTrie();
	~RWayTrie();
	void insert(const string& key, int val);
	bool contains(const string& key);
	int get(const string& key);
	void insertOrIncrement(const string& key);
};

#endif