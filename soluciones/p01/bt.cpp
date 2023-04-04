#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

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

// Ejercicio 2

void showMS(vector<int> &v, int n) {
  if (v.size() != n*n) {
    cout << "Invalid size of magic square...\n";
    return;
  }

  cout << "Magic sqr: " << endl;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      cout << v[i*n + j] << "  ";
    }
    cout << endl;
  }
  return;
}

int magicNum(int n){
  return (pow(n, 3) + n) / 2;
}

bool isMagic(int n, vector<int> &square, vector<int> &partialSums) {
  // al no tener partialSums antes tenia q calcularlas en el momento
  int magicN = magicNum(n);
  // usando available me aseguro que sean todos elementos distintos
  // creo q lo que falta asegurar es q las sumas den magicN
  bool allSumsEq = true;
  for (int sum: partialSums)
    allSumsEq &= (sum == magicN);
  return allSumsEq;
}


void ms(int &n, int &sol, vector<int> &partial, vector<bool> &available, vector<int> &partialSums) {
  // primeros dos elementos son sumas diagonales
  // n eltos sig son filas
  // ultimos n eltos son columnas

  int n2 = n*n;
  if (partial.size() == n2) {
    if (isMagic(n, partial, partialSums)) {
      sol++;
      showMS(partial, n);
    }
    return;
  }

  for(int i = 1; i <= n2; i++) {
    if (!available[i])
      continue;

    int magicN = magicNum(n),
        row = partial.size() / n, col = partial.size() % n,
        rowSum = partialSums[2 + row] + i, 
        colSum = partialSums[2 + n + col] + i,
        diag0Sum = partialSums[0] + ((row == col) ? i : 0),
        diag1Sum = partialSums[1] + ((row+col == n-1) ? i : 0);
    
    int last = n - 1;
    if (rowSum > magicN || colSum > magicN || diag0Sum > magicN || diag1Sum > magicN ||
        (row == last && colSum != magicN) || (col == last && rowSum != magicN) || 
        (row == col && row == last && diag0Sum != magicN) || (col == 0 && row == last && diag1Sum != magicN))
      continue; // podriamos contemplar qué elementos permiten sumar usando mi magicN - sumas parciales
    
    partialSums[2 + row] = rowSum; 
    partialSums[2 + n + col] = colSum;
    partialSums[0] = diag0Sum;
    partialSums[1] = diag1Sum;
    available[i] = false;
    partial.push_back(i);
    ms(n, sol, partial, available, partialSums);

    partialSums[2 + row] -= i;
    partialSums[2 + n + col] -= i;
    partialSums[0] -= ((row == col) ? i : 0),
    partialSums[1] -= ((row+col == n-1) ? i : 0);
    available[i] = true;
    partial.pop_back();
  }
}

void magic_sqr() {
  int n;
  cin >> n;
  vector<int> partialSol = {};
  vector<int> partialSums(n*2 + 2, 0);
  vector<bool> available(n*n + 1, true);
  int s = 0;
  ms(n, s, partialSol, available, partialSums);
  return;
}

// Ejercicio 3

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
  magic_sqr();
}