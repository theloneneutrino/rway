#include <iostream>
#include "rwaytrie.h"

using std::cout;
using std::endl;

int main()
{
  RWayTrie trieObj;
  const char * keys[] = {"was", "worst", "foolish"};
  if (trieObj.contains(keys[0]))
    cout << keys[0] << " repeated " << trieObj.get(keys[0]) << " times." << endl;
  else
    cout << "does not contain " << keys[0] << endl;
  cout << endl;
  if (trieObj.contains(keys[1]))
    cout << keys[1] << " repeated " << trieObj.get(keys[1]) << " times." << endl;
  else
    cout << "does not contain " << keys[1] << endl;
  cout << endl;
  if (trieObj.contains(keys[2]))
    cout << keys[2] << " repeated " << trieObj.get(keys[2]) << " times." << endl;
  else
    cout << "does not contain " << keys[2] << endl;
  cout << endl;
  cout << "End of test!\n";
}
