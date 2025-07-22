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

  /* These functions modify and retrieve the value of value in the node */
  void increment();
  void setVal(uint64_t);
  uint64_t getVal() const;
};

class RWayTrie {
  Node* root;
public:
  RWayTrie();
  ~RWayTrie();
  void insert(const char * key);
  void insert(const char * key, uint64_t val);
  bool contains(const char * key);
  uint64_t get(const char * key);
};

#endif
