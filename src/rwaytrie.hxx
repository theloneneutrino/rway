#ifndef RWAYTRIE_HXX
#define RWAYTRIE_HXX

#include <cstdint>

class Node {
private:
  static const int ALPHABET_SIZE = 256;
  std::uint64_t value;
  Node* next[ALPHABET_SIZE];
public:
  Node(int=0);
  ~Node();

  /* These functions handle the looking up and creation of the next nodes.
   * Originally, I had the RWayTrie doing this, but ideally all data that
   * belongs to a class or struct hould be handled by said class or struct. */
  Node * getNext(char) const;
  void createNext(char);

  /* These functions modify the value of value in the node */
  void increment();
  uint64_t getVal() const;
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
  uint64_t get(const char * key);
};

#endif
