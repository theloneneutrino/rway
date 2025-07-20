#ifndef RWAYTRIE_HXX
#define RWAYTRIE_HXX

#include <cstdint>

struct Node {
private:
  static const int ALPHABET_SIZE = 256;
public:
  std::uint64_t value;
  Node* next[ALPHABET_SIZE];
  Node(int=0);
  ~Node();
};

class RWayTrie {
  Node* root;
  Node* get(Node* x, const char * key, int d);
  Node* insert(Node* x, const char * key, int val, int d);
public:
  RWayTrie();
  ~RWayTrie();
  void insert(const char * key, int val);
  bool contains(const char * key);
  int get(const char * key);
  void insertOrIncrement(const char * key);
};

#endif
