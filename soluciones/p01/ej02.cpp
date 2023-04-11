#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

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

int main() {
  magic_sqr();
}