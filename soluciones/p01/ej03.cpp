#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

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
  //cout << "Nueva mejor solucion: {";
  cout << "{";
  for (int elem: vec)
    cout << elem << ", ";
  cout << "}" << endl;
}

void matSim(const vector<vector<int>> &M, const int &k, vector<bool> &solParcial, 
            vector<bool> &solFinal, int &sumaFinal, 
            vector<int> &sumasParciales, int tamParcial) {
  int sizeParcial = sizeBoolVec(solParcial);
  if (sizeParcial == k) {
    int sumaParcial = sumaMatEnI(M, solParcial); 
    showVec(solParcial);
    if (sumaParcial > sumaFinal) {
      cout << sumaParcial << endl;
      solFinal = solParcial;
      sumaFinal = sumaParcial;
    }
    return;
  }
  int rows = M.size();
  for (int i = tamParcial + 1; i < rows ; i++) {
    if (!solParcial[i])
      continue;
    
    solParcial[i] = false;
    matSim(M, k, solParcial, solFinal, sumaFinal, sumasParciales, i);
    solParcial[i] = true;
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
  vector<bool> solParcial(M.size(), true);
  vector<bool> solFinal = {};
  vector<int> sumasParciales = {};
  for (auto vec: M) {
    int sum = 0;
    for (int elem: vec)
      sum += elem;
    sumasParciales.push_back(sum);
  }
  int sumaFinal = -1;
  matSim(M, k, solParcial, solFinal, sumaFinal, sumasParciales, -1);
}

int main() {
  matriz_sim();
}