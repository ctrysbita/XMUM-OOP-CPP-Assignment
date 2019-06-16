#include <iostream>
#define CHARS_LEN 10

using namespace std;

/**
 * @brief Perform sequential search.
 * @param characters The array of characters.
 * @param target The target to search.
 * @return Index if found (start from 1). 0 if not found.
 */
size_t SequentialSearch(char characters[], char target) {
  for (size_t i = 0; i < CHARS_LEN; i++)
    if (characters[i] == target) return i + 1;
  return 0;
}

int main1() {
  char characters[CHARS_LEN] = {0};

  // Read characters to array.
  for (size_t i = 0; i < CHARS_LEN; i++) {
    cout << "Please input char " << i + 1 << ": ";
    char input;
  input:
    cin >> input;
    // Check if duplicated.
    if (SequentialSearch(characters, input) != 0) {
      cout << "Duplicated! Please input char " << i + 1 << " again: ";
      goto input;
    }
    characters[i] = input;
  }

  // Get target.
  char target;
  cout << "Please input the char to search: ";
  cin >> target;

  // Perform sequential search.
  auto searchResult = SequentialSearch(characters, target);
  if (searchResult == 0)
    cout << "Character '" << target << "' does not exist." << endl;
  else
    cout << "Found character '" << target << "' at " << searchResult << endl;

  return 0;
}