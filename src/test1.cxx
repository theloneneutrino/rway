#include <iostream>
#include "rwaytrie.h"

int main()
{
    RWayTrie trieObj;
    const char* keys[] = { "KeyOne", "KeyOn" };

    trieObj.insert(keys[0], 1);
    if (trieObj.contains(keys[0]))
        std::cout << "Contains " << keys[0] << "." << std::endl;
    else
        std::cout << "Doesn't contain " << keys[0] << "." << std::endl;

    if (trieObj.contains(keys[1]))
        std::cout << "Contains " << keys[1] << "." << std::endl;
    else
        std::cout << "Doesn't contain " << keys[1] << "." << std::endl;

    std::cout << "End of actions!" << std::endl;
    return 0;
}