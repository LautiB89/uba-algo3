#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

void showVec(const vector<int> &V) {
  for (int elem: V)
      cout << (elem < 0 ? "  " : "   ") << elem;
  cout << "\n";
}

void showMat(const vector<vector<int>> &M) {
  for (auto row: M)
    showVec(row);
}

int vecSum(const vector<int> &V) {
  int sum = 0;
  for (int num: V)
    sum += num;
  return sum;
}

template<typename T>
void espejar(const vector<vector<T>> &M) {
  // sirve para hacer simetricas a matrices cuadradas
  int rows = M.size(), cols = (rows > 0) ? M[0].size() : 0;
  for (int i = 0; i < rows; i++) {
    for (int j = i+1; j < cols; j++)
      M[i][j] = M[j][i];
  }
}