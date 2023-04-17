#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "mis-aux.cpp"

using namespace std;

/* 
Buscamos el conjunto de invitados mas grande tq
    no hay conflictos entre nadie
Tenemos un conjunto de invitados S
una representacion de los conflictos E

Funcion del item a
dado dos conjuntos S en V y W en V-S compatibles
devuelve el subconjunto de invitados mas grande de S
fs(S, W)
    | W vacio = S
    | 
*/

int n;
vector<vector<bool>> conflicto;

int main() {
    n = 5;
    conflicto = vector<vector<bool>> (n+1, vector<bool> (n+1, false));

    return 0;
}