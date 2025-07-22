#include <iostream>
#include "PG&E.h"
#include "rwaytrie.hxx"

using namespace std;

int main()
{
    RWayTrie trieObj;
    string text;

    cout << utils::console_colors::CYAN << "Please type or paste the following text and press Enter:" << utils::console_colors::RESET << endl;
    cout << utils::console_colors::GREEN << "\"It was the best of times, yet it was unpleasant times, there should be a wisdom, if not, it must have been the age of foolishness.\"" << utils::console_colors::RESET << endl;

    getline(cin, text);
    cout << endl;

    // Parse the text into words
    stringstream ss(text);
    string word;

    while (ss >> word) {
        // Clean each word (remove punctuation and convert to lowercase)
        string cleanedWord = utils::string_utils::cleanWord(word);

        // Insert or increment each word in the trie
        if (!cleanedWord.empty()) {
            trieObj.insert(cleanedWord.c_str());
        }
    }

    // Check and display count for "was"
    if (trieObj.contains("was"))
        cout << utils::console_colors::BRIGHT_GREEN << "was repeated " << utils::console_colors::BRIGHT_YELLOW << trieObj.get("was") << utils::console_colors::BRIGHT_GREEN << " times." << utils::console_colors::RESET << endl;
    else
        cout << utils::console_colors::BRIGHT_RED << "does not contain was" << utils::console_colors::RESET << endl;
    cout << endl;

    // Check and display count for "worst" (should not exist)
    if (trieObj.contains("worst"))
        cout << utils::console_colors::BRIGHT_GREEN << "worst repeated " << utils::console_colors::BRIGHT_YELLOW << trieObj.get("worst") << utils::console_colors::BRIGHT_GREEN << " times." << utils::console_colors::RESET << endl;
    else
        cout << utils::console_colors::BRIGHT_RED << "does not contain worst" << utils::console_colors::RESET << endl;
    cout << endl;

    // Check and display count for "foolish"
    if (trieObj.contains("foolish"))
        cout << utils::console_colors::BRIGHT_GREEN << "foolish repeated " << utils::console_colors::BRIGHT_YELLOW << trieObj.get("foolish") << utils::console_colors::BRIGHT_GREEN << " times." << utils::console_colors::RESET << endl;
    else
        cout << utils::console_colors::BRIGHT_RED << "does not contain foolish" << utils::console_colors::RESET << endl;
    cout << endl;

    cout << utils::console_colors::MAGENTA << "End of test!" << utils::console_colors::RESET << endl << endl;
}
