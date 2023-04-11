#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Ejercicio 1

bool validSol(vector<int> s, int k) { 
  int sum = 0, n = s.size();
  for(int i = 0; i < n; i++)
    sum += s[i];
  return (sum == k); 
}

void ss(vector<int> &s, vector<int> &partialSol, vector<vector<int>> &sol, int i, int &k) {
  if (s.size() == i) {
    if (validSol(partialSol, k)){
      sol.push_back(partialSol);
    }
    return;
  }
  partialSol.push_back(s[i++]);
  ss(s, partialSol, sol, i, k);
  partialSol.pop_back();
  ss(s, partialSol, sol, i, k);
  return;
};

vector<vector<int>> subset_sum(vector<int> input_set, int k) {
  // devuelve todos los subconjuntos de s que suman k
  // s es un multiconjunto de enteros
  // k un entero
  vector<vector<int>> sol = {};
  vector<int> partialSol = {};
  ss(input_set, partialSol, sol, 0, k);
  return sol;
}

int main() {
  subset_sum({6,12,6}, 6);
}