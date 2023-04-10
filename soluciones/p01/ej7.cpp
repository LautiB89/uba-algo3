#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "mis-aux.cpp"

using namespace std;
const int BOTTOM = -1;

/* 
Si tengo c asteroides en el dia j con c not in [0,j] entonces:
    - "debo" asteroides, algo que no está permitido
    - o no voy a poder vender todos los que tengo
Asi que nunca puedo permitir un c que no esté en [0,j]

mgn(j, c) = maximo entre
    - mgn(j-1, c-1) // vender un asteroide en el dia j
    - mgn(j-1, c+1) // comprar un asteroide en el dia j - aca sumo ganancia
    - mgn(j-1, c)   // no hacer nada en el dia j

Maxima ganancia neta  tratando de nunca llegar a un caso indefinido
no se si está bien
mgn(j, c) | (j <= 0)     = 0
          | (c == 0 && j == 1)    = mgn(j-1, c)
          | (c == j) = mgn(j-1, c-1)
          | (c == j-1) = max(mgn(j-1, c), mgn(j-1, c+1))
          | (c == 0) = max(mgn(j-1, c), mgn(j-1, c-1))
          | otherwise = max(mgn(j-1, c), mgn(j-1, c-1), mgn(j-1, c+1))

mgn(j, c) | (j < 0 || j > c) = -inf
          | (j == 0) = 0
          | otherwise = max(mgn(j-1, c+1) + p_j ,
                            mgn(j-1, c-1) - p_j ,
                            mgn(j-1, c) )

Usando esta formulacion de mgn, resolvemos el problema usando mgn(j, 0)
 */

vector<int> p = {3,2,5,6};
int n = 3;
vector<vector<int>> memo(n+1, vector<int>(p.size() + 1, BOTTOM));
// en realidad no necesitamos |p|, con |p|/2 alcanza

int mgnTopDown(int dia, int cant) {
    // espacial: O(n²) por la matriz
    // temporal: n² estados 
    if (cant < 0 || cant > dia) 
        return INT16_MIN;
    if (dia == 0)
        return 0;

    if (memo[dia][cant] == BOTTOM)
        memo[dia][cant] = max(mgnTopDown(dia-1, cant-1) - p[dia-1], 
                          max(mgnTopDown(dia-1, cant+1) + p[dia-1],
                              mgnTopDown(dia-1, cant)));
    return memo[dia][cant];
}

int mgnBottomUp(int dia, int cant) {
    // espacial: O(n) por la matriz
    // temporal: n² estados 

    vector<int> memoBU(n+1, BOTTOM);
    for (int i = 1; i < dia; i++) {
        for (int j = 1; j <= i; j++) {
            memoBU[j]// ver qe hacer
        }
    }
}

int main() {
    cout << mgnTopDown(n, 0) << endl;
    showMat(memo);
}