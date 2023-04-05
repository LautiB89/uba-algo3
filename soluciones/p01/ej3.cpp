#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int sumaMatEnI(const vector<vector<int>> &M, vector<bool> &solParcial) {
  int sum = 0, rows = M.size(), cols = M[0].size();
  for (int i = 0; i < rows; i++) {
    for (int j = i; j < cols; j++) {
      sum += M[i][j] * solParcial[i] * solParcial[j] * ((i != j) + 1);
    }
  }
  return sum;
}

int sizeBoolVec(vector<bool> &solParcial) {
  int size = 0;
  for (bool val: solParcial)
    size += int(val);
  return size;
}

void showVec(const vector<bool> &vec) {
  cout << "Nueva mejor solucion: {";
  for (int elem: vec)
    cout << elem << ", ";
  cout << "}" << endl;
}

void matSim(const vector<vector<int>> &M, const int &k, vector<bool> &solParcial, vector<bool> &solFinal, int &sumaFinal) {
  int sizeParcial = sizeBoolVec(solParcial);
  if (sizeParcial == k) {
    int sumaParcial = sumaMatEnI(M, solParcial); 
    if (sumaParcial > sumaFinal) {
      showVec(solParcial);
      cout << sumaParcial << endl;
      solFinal = solParcial;
      sumaFinal = sumaParcial;
    }
    return;
  }
  int rows = M.size();
  for (int i = 0; i < rows; i++) {
    if (solParcial[i])
      continue;
    
    int sumaUsandoI = 0;
    int sumaParcial = sumaMatEnI(M, solParcial); 
    
    for (int j = 0; j < rows; j++)
      sumaUsandoI += M[i][j] * solParcial[j] * ((i != j) + 1);
    
    if (sumaParcial + sumaUsandoI <= sumaFinal)
      continue;
    
    solParcial[i] = true;
    matSim(M, k, solParcial, solFinal, sumaFinal);
    solParcial[i] = false;
  }
}

void matriz_sim() {
  vector<vector<int>> M = {
    {0,  10, 10, 1},
    {10, 0,  5,  2},
    {10, 5,  0,  1},
    {1,  2,  1,  0}
  };
  int k;
  cin >> k;
  vector<bool> solParcial(M.size(), false);
  vector<bool> solFinal = {};
  int sumaFinal = -1;
  matSim(M, k, solParcial, solFinal, sumaFinal);
}

int main() {
  matriz_sim();
}