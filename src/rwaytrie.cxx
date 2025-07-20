#include "rwaytrie.hxx"

Node::Node(int value)
{
  this->value = value;

  for (int i = 0; i < ALPHABET_SIZE; i++)
    next[i] = nullptr;
}

Node::~Node()
{
  for (int i = 0; i < ALPHABET_SIZE; i++)
    if(next[i] != nullptr)
      delete next[i];
}

RWayTrie::RWayTrie()
{
  root = new Node();
}

RWayTrie::~RWayTrie()
{
  delete root;
}

void RWayTrie::insert(const char * key, int val)
{
  // TODO: implement this function
}

bool RWayTrie::contains(const char * key)
{
  uint64_t value = 0;
  return value;
}

uint64_t RWayTrie::get(const char * key)
{
  return 0;
}

void RWayTrie::insertOrIncrement(const char * key){}
