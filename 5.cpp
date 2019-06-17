#include <iostream>
#include <vector>

using namespace std;

class Matrix {
 private:
  size_t rows, cols;
  vector<vector<double>> values;

  // Prevent constructing matrix without specifying cols and rows.
  Matrix();

  // Check if the
  bool canAdd(Matrix other) { return other.rows == rows && other.cols == cols; }

 public:
  Matrix(size_t cols, size_t rows) : cols(cols), rows(rows) {
    // Resize vector to match the specified size.
    values.resize(rows);
    for (auto &row : values) row.resize(cols);

    // Input matrix.
    cout << "Please input matrix (" << rows << " x " << cols << "): " << endl;
    for (auto &row : values)
      for (auto &col : row) cin >> col;
  }

  void display() {
    cout << "-- Matrix " << rows << " x " << cols << " --" << endl;
    for (auto &row : values) {
      for (auto &col : row) cout << col << " ";
      cout << endl;
    }
  }

  friend Matrix operator+(const Matrix &me, const Matrix &other) {
    if (other.rows != me.rows || other.cols != me.cols) {
      cout << "Cannot add two matrix with different size" << endl;
      return me;
    }

    auto result = Matrix(me);

    for (size_t i = 0; i < me.rows; i++)
      for (size_t j = 0; j < me.cols; j++)
        result.values[i][j] += other.values[i][j];
    return result;
  }
};

int main() {
  size_t cols, rows;
  cout << "Please enter the size of first Matrix: ";
  // MSVC compiler use scanf_s instead scanf due to security problem.
#ifdef _MSC_VER
  scanf_s("%zux%zu", &cols, &rows);
#else
  scanf("%zux%zu", &cols, &rows);
#endif
  Matrix m1(cols, rows);
  m1.display();

  cout << "Please enter the size of second Matrix: ";
  // MSVC compiler use scanf_s instead scanf due to security problem.
#ifdef _MSC_VER
  scanf_s("%zux%zu", &cols, &rows);
#else
  scanf("%zux%zu", &cols, &rows);
#endif
  Matrix m2(cols, rows);
  m2.display();

  auto m3 = m1 + m2;
  cout << "Result of sum: " << endl;
  m3.display();

  return 0;
}