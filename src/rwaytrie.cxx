#include "rwaytrie.hxx"

/* ┌────────────────────────────────────────────────┐
 * │ The following functions are for the Node class │
 * └────────────────────────────────────────────────┘ */

Node::Node(int value) : value(value) {
  for (int i = 0; i < ALPHABET_SIZE; i++) {
     next[i] = nullptr;
  }
}

Node::~Node(){
  for (int i = 0; i < ALPHABET_SIZE; i++) {
     if (next[i] != nullptr)
       delete next[i];
  }
}

Node * Node::getNext(char a) const
{
  return this->next[uint8_t(a)];
}
void Node::createNext(char a)
{
  this->next[uint8_t(a)] = new Node();
}

void Node::increment()
{
  this->value++;
}

void Node::setVal(uint64_t value)
{
  this->value = value;
}

uint64_t Node::getVal() const
{
  return this->value;
}

/* ┌────────────────────────────────────────────────────┐
 * │ The following functions are for the RWayTrie class │
 * └────────────────────────────────────────────────────┘ */

RWayTrie::RWayTrie()
{
  root = new Node();
}


RWayTrie::~RWayTrie()
{
  delete root;
}

void RWayTrie::insert(const char * key)
{
  Node * tmpnode = root;
  const char * a = &key[0];

  while (*a != 0)
  {
    if (tmpnode->getNext(*a) == nullptr) /* if the node doesn't exist, create it */
      tmpnode->createNext(*a);

    tmpnode = tmpnode->getNext(*a);
    a += sizeof(char);
  }
  tmpnode->increment(); /* At the end of the chain, increment val */
}

void RWayTrie::insert(const char * key, uint64_t value)
{
  Node * tmpnode = root;
  const char * a = &key[0];

  while (*a != 0)
  {
    if (tmpnode->getNext(*a) == nullptr) /* if the node doesn't exist, create it */
      tmpnode->createNext(*a);

    tmpnode = tmpnode->getNext(*a);
    a += sizeof(char);
  }
  tmpnode->setVal(value); /* At the end of the chain, set val */
}

bool RWayTrie::contains(const char * key)
{
  Node * tmpnode = root;
  const char * a = &key[0];

  while (*a != 0)
  {
    if (tmpnode->getNext(*a) == nullptr)
      return false;
    else
      tmpnode = tmpnode->getNext(*a);

    a += sizeof(char);
  }
  return tmpnode->getVal() != 0;
}

uint64_t RWayTrie::get(const char * key)
{
  Node * tmpnode = root;
  const char * a = &key[0];

  while (*a != 0)
  {
    if (tmpnode->getNext(*a) == nullptr)
      return 0;
    else
      tmpnode = tmpnode->getNext(*a);

    a += sizeof(char);
  }
  return tmpnode->getVal();
}
