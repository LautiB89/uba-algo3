#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "mis-aux.cpp"

using namespace std;

/* 
Distinguibles: acá importa el orden
    1 1 4 es distinto 1 4 1
n = #dados
k = valor max de los dados
s = suma que queremos hacer de una tirada

f(n, s) devuelve las permutaciones de n eltos 
tal que la suma da s

f(n, s)
    | (s <= 0)  = 0
    | (n == 1)  = (s <= k)  (sii s puede salir en un dado)
    | otherwise = sum_i=1^k( f(n-1, s-i) )

Vale!!!
k = 4
f(3, 6) =
    f(2, 5) 4
        f(1, 4) 1
        f(1, 3) 1
        f(1, 2) 1
        f(1, 1) 1
    f(2, 4) 3
        f(1, 3) 1
        f(1, 2) 1
        f(1, 1) 1
        f(1, 0) 0
    f(2, 3) 2
        f(1, 2)  1
        f(1, 1)  1
        f(1, 0)  0
        f(1, -1) 0
    f(2, 2) 1
        f(1, 1)  1
        f(1, 0)  0
        f(1, -1) 0
        f(1, -2) 0

f(n, s, k) ahora tambien pasamos los valores de los dados
esto nos permite acotar los valores 
que pueden tomar los dados del paso recursivo

g(n, s, k)
    | (s <= 0) || (k <= 0) = 0
    | (n == 1)  = (s <= k)  (sii s puede salir en un dado)
    | otherwise = sum_i=1^k( g(n-1, s-i, i) )

Vale!!! 
g(3, 6, 4) 2
    1 g(2, 5, 1)
        1 g(1, 4, 1) 0

    2 g(2, 4, 2)
        1 g(1, 3, 1) 0
        2 g(1, 2, 2) 1

    3 g(2, 3, 3)
        1 g(1, 2, 1) 0
        2 g(1, 1, 2) 1
        3 g(1, 0, 3) 0

    4 g(2, 2, 4)
        1 g(1, 1, 1) 1
        2 g(1, 0, 2) 0
        3 g(1, -, 3) 0
        4 g(1, -, 4) 0

Demostrar que f y g tienen superposicion de problemas.

 */

/* 
f(n, s) devuelve las permutaciones de n eltos 
tal que la suma da s

f(n, s)
    | (s <= 0)  = 0
    | (n == 1)  = (s <= k)  (sii s puede salir en un dado)
    | otherwise = sum_i=1^k( f(n-1, s-i) )
 */

const int BOTTOM = -1;
int k1 = 4, n1 = 3, s1 = 6;
vector<vector<int>> memo(n1+1, vector<int>(s1+1, BOTTOM));

int fTD(int n, int s, int k) {
    if (s <= 0) return 0;
    //aca podria considerar que si n=0 y s=0 tengo 1 perm que cumple
    // entonces el caso (1, s) se trata en la recursion
    //if (n == 0) return (s == 0);
    if (n == 1) return int(s <= k);
    if (memo[n][s] == BOTTOM) {
        int sum = 0;
        for(int i = 1; i <= k; i++) {
            sum += fTD(n-1, s-i, k);
        }
        memo[n][s] = sum;
    }
    return memo[n][s];
}

int gTD(int n, int s, int k) {
    if (s <= 0 || k <= 0) return 0;
    //aca podria considerar que si n=0 y s=0 tengo 1 perm que cumple
    // entonces el caso (1, s) se trata en la recursion
    //if (n == 0) return (s == 0);
    if (n == 1) return int(s <= k);
    
    if (memo[n][s] == BOTTOM) {
        int sum = 0;
        for(int i = 1; i <= k; i++) {
            sum += gTD(n-1, s-i, i);
        }
        memo[n][s] = sum;
    }
    return memo[n][s];
}

int main() {
    fTD(n1, s1, k1);
    showMat(memo);
    cout << "\n";
    memo = vector<vector<int>>(n1+1, vector<int>(s1+1, BOTTOM));
    gTD(n1, s1, k1);
    showMat(memo);
}