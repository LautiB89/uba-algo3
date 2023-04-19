#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "mis-aux.cpp"

using namespace std;


// Solucion dinamica

/* 
act(A, S, i) 
devuelve el conjunto maximo de activades que
    contiene a S , con S incluido en {A1, ..., Ai-1}
    es obtenido unicamente con elementos en {Ai, ..., An}

Cada actividad A tiene 
    A.s (tiempo inicial)
    A.f (tiempo final)

act(A, S, i)    <--- este hay que arrancarlo con i=0
    | i == n+1 = S
    | i > 1 && A[i-1].f > A[i].s = act(A, S, i+1)
    | otherwise = mas grande entre act(A, S, i+1) y act(A, S U {A[i]}, i+1)

act(A, S, i)    <--- este hay que arrancarlo con i=n
    | i == 0 = S
    | i < n && A[i].f > A[i+1].s = act(A, S, i-1)
    | otherwise = mas grande entre act(A, S, i-1) y act(A, S U {A[i]}, i-1)
*/
const int BOTTOM = -1;
int n = 5; // cantidad de actividades (son numeros de 1 a n)
vector<int> s = {0, 1, 3, 3, 4, 5}; //tiempo inicial de cada actividad
vector<int> t = {0, 2, 6, 4, 5, 6}; //tiempo final   de cada actividad
vector<vector<int>> memo(n+1, vector<int>(n*2+1, BOTTOM));

bool puedoAgregar(int final_t, int i) {
    return final_t <= s[i]; //defino s y t de forma que siempre pueda agregar i=1
}

int largo(int i) {
    return t[i] - s[i];
}

int actDP(int i = 1, int ultHr = 1) { //devuelvo el tamaño del conj mas grande posible
    if (i == n) //asi nos aseguramos el i > 1 de act(A, S, i)
        return (int) puedoAgregar(ultHr, i);

    if (memo[i][ultHr] == BOTTOM) {
        memo[i][ultHr] = puedoAgregar(ultHr, i) ?
                            max(actDP(i+1, ultHr), actDP(i+1, t[i]) + 1) :
                            actDP(i+1, ultHr);
    }
    return memo[i][ultHr];
}

/* int actGreedy() {
    int tMax = 1;
    for (int i = 0; i <= n; i++) {
        
    }
}
 */
int main() {
    cout << "aalertaaa!!! \a" << endl;
    actDP();
    showMat(memo);
    return 0;
}