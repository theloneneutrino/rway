#include <print>
#include "rwaytrie.hxx"
#include "ansi.hxx"

int main()
{
  RWayTrie trieObj;
  const char * keys[] = {"KeyOne", "KeyOn"};

  trieObj.insert(keys[0], 1);
  if (trieObj.contains(keys[0]))
    std::println("Contains {}{}{}.", ANSI::GREEN, keys[0], ANSI::RESET);
  else
    std::println("Doesn't contain {}{}{}.", ANSI::RED, keys[0], ANSI::RESET);

  if (trieObj.contains(keys[1]))
    std::println("Contains {}.", keys[1]);
  else
    std::println("Doesn't contain {}.", keys[1]);

  std::println("End of actions!");
}
