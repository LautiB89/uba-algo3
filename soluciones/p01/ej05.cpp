#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "mis-aux.cpp"

using namespace std;

int ssTopDown(const vector<int> &C, int i, int j, vector<vector<int>> &memo) {
  // devuelvo cuantas soluciones existen
  if (j < 0)
    return 0;
  if (i == 0) 
    return (j == 0);
  

  if (memo[i][j] != -1) {
    return memo[i][j];
  } 

  memo[i][j] = ssTopDown(C, i-1, j, memo);
  if (j - C[i-1] >= 0)
    memo[i][j] += ssTopDown(C, i-1, j-C[i-1], memo);
  
  return memo[i][j];
};

int TopDownSolution() {
  int k;
  cin >> k;
  vector<int> entrada = {1,3,2};
  vector<vector<int>> memo(k+1, vector<int>(entrada.size() + 1, -1));
  memo[0] = vector<int>(entrada.size() + 1, 0);
  memo[0][0] = 1;
  cout << ssTopDown(entrada, entrada.size(), k, memo) << endl;
  showMat(memo);
}

int lessSpaceBottomUp(const vector<int> &C, int k) {
  // devuelvo cuantas soluciones existen  
  vector<int> memo(k+1, 0);
  memo[0] = 1;
  
  for (int i = 1; i <= C.size(); i++) {
    for (int j = k; j >= 0; j--) {
      if (j - C[i-1] >= 0)
        memo[j] += memo[j - C[i-1]];
    }
  }
  showVec(memo);
  return memo[k];
};

int lessSpaceMain() {
  int k;
  cin >> k;
  vector<int> entrada = {1,3,2};
  cout << lessSpaceBottomUp(entrada, k) << endl;
}

int main() {
  lessSpaceMain();
}