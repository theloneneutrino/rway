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

}
