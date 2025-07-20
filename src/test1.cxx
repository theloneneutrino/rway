#include <print>
#include "rwaytrie.hxx"

int main()
{
  RWayTrie trieObj;
  const char * keys[] = {"KeyOne", "KeyOn"};

  trieObj.insert(keys[0], 1);
  if (trieObj.contains(keys[0]))
    std::println("Contains {}.", keys[0]);
  else
    std::println("Doesn't contain {}.", keys[0]);

  if (trieObj.contains(keys[1]))
    std::println("Contains {}.", keys[1]);
  else
    std::println("Doesn't contain {}.", keys[1]);

  std::println("End of actions!");
}
