#include <print>
#include "rwaytrie.hxx"
#include "ansi.hxx"

int main()
{
    RWayTrie trieObj;
    const char* keys[] = { "KeyOne", "KeyOn" };

  trieObj.insert(keys[0], 1);
  if (trieObj.contains(keys[0]))
    std::println("Contains {}{}{}.", ANSI::GREEN, keys[0], ANSI::RESET);
  else
    std::println("Doesn't contain {}{}{}.", ANSI::RED, keys[0], ANSI::RESET);

  if (trieObj.contains(keys[1]))
    std::println("Contains {}{}{}.", ANSI::GREEN, keys[1], ANSI::RESET);
  else
    std::println("Doesn't contain {}{}{}.", ANSI::RED, keys[1], ANSI::RESET);

  std::println("End of actions!");
  return 0;
}
