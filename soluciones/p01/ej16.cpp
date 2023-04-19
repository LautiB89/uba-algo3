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

int n = 5;
int cant = n, cantParcial = 0, cantFinal = 0;
vector<vector<bool>> conflicto(n+1, vector<bool> (n+1, false));
vector<bool> parcial(n+1, false);
vector<bool> final(n+1, false);
vector<bool> disponibles(n+1, true);

// vector<bool> filtrarConflictos(const vector<bool> &C)

void fiestaBT() {
    if (cant == 0) {
        // printf("Llegue a una hoja: \n");
        // showVec(parcial);
        // showVec(disponibles);
        if (cantParcial >= cantFinal) {
            // printf("y es la mejor!!! p=%d, f=%d\n", cantParcial, cantFinal);
            final = parcial; cantFinal = cantParcial;
        }
        return;
    }

    // poda
    if (cantParcial + cant < cantFinal) return;

    // Saco w de la lista disponibles (W) (alguno disponible)
    int w = 0;
    for (int i = 1; i <= n && w == 0; i++) {
        if (disponibles[i])
            w = i;
    }
    disponibles[w] = false;
    cant--;
    fiestaBT(); // en este caso entra parcial sin tocar, y W sin w
    
    // Filtro disponibles
    vector<bool> aux = disponibles;
    for (int i = 1; i <= n; i++) {
        disponibles[i] = aux[i] && !conflicto[w][i];
    }
    
    // Agrego w a la solucion parcial
    parcial[w] = true;
    cantParcial++;
    fiestaBT();

    // Deshago mis cambios (importante por ser globales)
    cant++;
    disponibles = aux;
    disponibles[w] = true;
    parcial[w] = false;
    cantParcial--;
    
    return;
}

int main() {
    conflicto[1][2] = true;
    conflicto[2][3] = true;
    conflicto[3][4] = true;
    conflicto[4][5] = true;

    espejar(conflicto);
    // showMat(conflicto);
    fiestaBT();
    showVec(final);
    return 0;
}