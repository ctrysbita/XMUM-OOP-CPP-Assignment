#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Perform sequential search.
 * @param vector The vector<T> to search.
 * @param target The target to search.
 * @return Index if found (start from 1). 0 if not found.
 */
template <typename T>
size_t SequentialSearch(vector<T> vec, T target) {
  for (size_t i = 0; i < vec.size(); i++)
    if (vec[i] == target) return i + 1;
  return 0;
}

/**
 * @brief Display vector.
 * @param vector The vector<T> to display.
 */
template <typename T>
void display(vector<T> vec) {
  for (auto i : vec) cout << i << " ";
  cout << endl;
}

int main2() {
  vector<int> vec;

  // Get size n.
  size_t n;
  cout << "Please input the total number to input: ";
  cin >> n;

  // Input to vector.
  for (size_t i = 0; i < n; i++) {
    int input;
    cout << "Please input NO." << i + 1 << " number : ";
    cin >> input;
    vec.push_back(input);
  }
  cout << "Vector: ";
  display(vec);

  // Get key.
  int key;
  cout << "Please input the key to search: ";
  cin >> key;

  // Perform sequential search.
  auto searchResult = SequentialSearch(vec, key);
  if (searchResult == 0)
    cout << "Key '" << key << "' does not exist." << endl;
  else
    cout << "Found key '" << key << "' at " << searchResult << endl;

  // Sort all.
  auto vecForSort = vec;
  sort(vecForSort.begin(), vecForSort.end());
  cout << "Sorted vector: ";
  display(vecForSort);

  // Sort second half.
  auto vecForHalfSort = vec;
  sort(vecForHalfSort.begin() + vecForHalfSort.size() / 2,
       vecForHalfSort.end());
  cout << "Second half sorted vector: ";
  display(vecForHalfSort);

  // Using erase & clear.
  auto vecForErase = vec;
  cout << "Erase first element: ";
  vecForErase.erase(vecForErase.begin());
  display(vecForErase);

  auto vecForEraseHalf = vec;
  cout << "Erase first half elements: ";
  vecForEraseHalf.erase(vecForEraseHalf.begin(),
                        vecForEraseHalf.begin() + vecForEraseHalf.size() / 2);
  display(vecForEraseHalf);

  auto vecForClear = vec;
  vecForClear.clear();
  cout << "Vector fter clear: ";
  display(vecForClear);

  return 0;
}