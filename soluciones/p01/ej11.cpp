#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "mis-aux.cpp"

using namespace std;
const string BOTTOM = "⊥";

const string SUM = "+ ";
const string MUL = "* ";
const string POT = "^ ";

/* 
v = (v1, v2, ..., vn) un vector de numeros naturales
w un numero natural

ops(n, w) = 

ops(n-1, w, vn) = ops(n-2, w, v[n-1] + v[n])

ops(n, w)
    | (n == 1) && (w == v1) = []
    | sum != BOTTOM = sum ++ "+"
    | mul != BOTTOM = mul ++ "x"
    | pot != BOTTOM = pot ++ "^"
    | otherwise = BOTTOM
    where 
        sum = ops(n-1, w-vn)    
        mul = ops(n-1, w//vn)   
        pot = ops(n-1, w^(1/vn))

ops(i, k)
    | (i == n+1) && (w == k) = []
    | (i == 1) = ops(2, v1)
    | sum != BOTTOM = "+" : sum 
    | mul != BOTTOM = "x" : mul 
    | pot != BOTTOM = "^" : pot 
    | otherwise = BOTTOM
    where
        sum = ops(i+1, k + vi)
        mul = ops(i+1, k * vi)
        pot = ops(i+1, k ^ vi)
*/

vector<int> v = {3,1,5,2,1};
int n = v.size(),
    w = 400;
vector<vector<string>> memo(n+1, vector<string>(w+1, BOTTOM));

string opsTP(int i, int k) {
    // printf("i = %d, k = %d\n", i, k);
    if (i == n)
        return k == w ? "" : BOTTOM;    // para empezar a construir la solucion
    if (k > w)                          // ya se que i != n (i < n)
        return BOTTOM;

    if (memo[i][k] == BOTTOM) {
        string sum = opsTP(i+1, k + v[i]);
        string mul = opsTP(i+1, k * v[i]);
        string pot = opsTP(i+1, pow(k, v[i]));
        memo[i][k] = sum != BOTTOM ? SUM + sum :
                     mul != BOTTOM ? MUL + mul :
                     pot != BOTTOM ? POT + pot : BOTTOM;
    }
    return memo[i][k];
}

int main() {
    cout << "Solucion final: " << opsTP(1, v[0]) << endl;
}