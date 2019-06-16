#include <iostream>
#include <vector>
#define ARR_SIZE 10

using namespace std;

int main3() {
  size_t arrLen;
  cout << "Please specify the length of vector: ";
  cin >> arrLen;

  // Initiate array and vector.
  // Array initlialized with fixed length due to MSVC doesn't support VLA.
#if _MSC_VER
  int array[ARR_SIZE];
  if (ARR_SIZE < arrLen) exit(1);
#else
  int array[arrLen];
#endif
  vector<int> vec;

  // Input elements to array & vector.
  for (size_t i = 0; i < arrLen; i++) {
    int temp;
    cout << "Please enter NO." << i + 1 << " number: ";
    cin >> temp;
    array[i] = temp;
    vec.push_back(temp);
  }

  // Using array.
  cout << "Sum of each pair of adjacent elements in array:" << endl;
  for (size_t i = 0; i < arrLen - 1; i++)
    cout << array[i] + array[i + 1] << " ";

  cout << endl
       << "Sum of the first and last elements, second and second-to-last... in "
          "array:"
       << endl;
  for (size_t i = 0, j = arrLen - 1; i < j; i++, j--)
    cout << array[i] + array[j] << " ";

  // Using vector and iterator.
  cout << endl << "Sum of each pair of adjacent elements in vector:" << endl;
  for (auto it = vec.begin(); it != vec.end() - 1; it++)
    cout << *it + *(it + 1) << " ";

  cout << endl
       << "Sum of the first and last elements, second and second-to-last... in "
          "vector:"
       << endl;
  for (auto itFront = vec.begin(), itBack = vec.end() - 1; itFront < itBack;
       itFront++, itBack--)
    cout << *itFront + *itBack << " ";

  return 0;
}