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
