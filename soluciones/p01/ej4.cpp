#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "mis-aux.cpp"
using namespace std;

// Tomo el aproach mas fuerza bruta, generando cada permutación:

vector<vector<int>> M = {
    {0,  1,  10, 10},
    {10, 0,  3,  15},
    {21, 17, 0,  2},
    {3,  22, 30, 0},
};
vector<int> parcial = {};
vector<int> pi = {};
vector<int> final = {};
int sumaFinal = INT32_MAX;
int n = 4;

void permMin(int sumaParcial, vector<bool> &disponible, int cantRestantes) {
    if (cantRestantes == 0) {
        int prox = M[ pi[pi.size()-1]-1 ][ pi[0]-1 ];
        parcial.push_back(prox);
        sumaParcial += prox;
        if (sumaParcial <= sumaFinal) {
            printf("nueva mejor solución --> ");
            showVec(pi);
            final = parcial;
            sumaFinal = sumaParcial;
        }
        parcial.pop_back();
        return;
    }
    cantRestantes--;
    for (int i = 1; i <= n; i++) {
        if (!disponible[i]) continue;
        int prox = 0;
        if (pi.size() > 0) {
            prox = M[ pi[pi.size()-1] - 1 ][i-1];
            if (sumaParcial + prox >= sumaFinal)
                continue; // poda por optimalidad
            parcial.push_back(prox);
        }
        
        pi.push_back(i);
        disponible[i] = false;
        permMin(sumaParcial + prox, disponible, cantRestantes);
        pi.pop_back();
        if (pi.size() > 0)
            parcial.pop_back();
        disponible[i] = true;
    }
    return;
}

int main() {
    vector<bool> disponibles(n+1, true);
    permMin(0, disponibles, n);
}