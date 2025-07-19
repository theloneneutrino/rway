#include <iostream>
#include <string>
#include "rwaytrie.h"
#include "pge.h"  //which ever part you choose to make please include the new header here 

using namespace std;

void testQ1() {
    cout << "Q1: Basic R-way Trie Test" << endl;
    cout << "=========================" << endl;

    RWayTrie trieObj;

    // TODO: Insert "KeyOne" with value 1

    // TODO: Check if trie contains "KeyOne"


    // TODO: Check if trie contains "KeyOn" 


    cout << "End of actions!\n" << endl;
}

void testQ2() {
    cout << "Q2: Word Counting with R-way Trie" << endl;
    cout << "==================================" << endl;

    RWayTrie trieObj;
    string text;

    cout << "Please type or paste the following text and press Enter:" << endl;
    cout << utils::console_colors::GREEN << "\"It was the best of times, yet it was unpleasant times, there should be a wisdom, if not, it must have been the age of foolishness.\"" << utils::console_colors::RESET << endl;

    getline(cin, text);
    cout << endl;

    // TODO: Parse the text into words
    // TODO: Clean each word
    // TODO: Insert or increment each word in the trie


    // TODO: Check and display count for "was"


    // TODO: Check and display count for "worst" (should not exist)


    // TODO: Check and display count for "foolish"


    cout << "End of test!\n" << endl;
}

int main() {
    testQ1();
    testQ2();

    return 0;
}
