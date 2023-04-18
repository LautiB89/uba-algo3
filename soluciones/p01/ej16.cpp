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
la idea es resolver nuestro problema usando fs(vacio, V)

fs(S, W)
    | W vacio   = S
    | otherwise = mas grande entre fs(S, W-{w}) y fs(S U {w}, W filtrado)
        donde w = alguno de W

{{1, 2}, {2, 3}, {3, 4}, {4, 5}}

fs({}, {1, 2, 3, 4, 5})
    fs({}, {1, 2, 3, 4})
    fs({1}, {1, 2, 3, 4, 5})
*/ 

int n;
vector<vector<bool>> conflicto;
vector<int> parcial = {};
vector<int> final = {};

void fiestaBT(vector<int> disponibles) {
    if (disponibles.empty()) {
        if (parcial.size() > final.size())
            final = parcial;
        return;
    }

    int w = disponibles.back();
    disponibles.pop_back();
    fiestaBT(disponibles); // en este caso entra parcial sin tocar, y W sin w

    auto it = disponibles.begin();
    while (it != disponibles.end()) {
        if (conflicto[*it][w]) {
            disponibles.erase(it);
        } else {
            it++;
        }
    } // resolver este quilombo
    
    fiestaBT(disponibles);

    return;
}


int main() {
    n = 5;
    vector<int> disponibles = {1,2,3,4,5};
    conflicto = vector<vector<bool>> (n+1, vector<bool> (n+1, false));
    conflicto[1][2] = true;
    conflicto[2][3] = true;
    conflicto[3][4] = true;
    conflicto[4][5] = true;
    espejar(conflicto);

    fiestaBT(disponibles);
    showVec(parcial);
    return 0;
}