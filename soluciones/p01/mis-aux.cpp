#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

template<typename T>
void showVec(const vector<T> &V) {
  for (auto elem: V)
      cout << elem << "\t";
  cout << "\n";
}

void showVec(const vector<bool> &V, bool ignoreZero = true) {
  int n = V.size();
  for (int i = ignoreZero; i < n; i++) {
    if (V[i])
      cout << i << "\t";
  }
  cout << "\n";
}

template<typename T>
void showMat(const vector<vector<T>> &M) {
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
void espejar(vector<vector<T>> &M) {
  // sirve para hacer simetricas a matrices cuadradas
  int rows = M.size(), cols = (rows > 0) ? M[0].size() : 0;
  for (int i = 0; i < rows; i++) {
    for (int j = i+1; j < cols; j++) {
      M[j][i] = M[i][j];
    }
  }
}