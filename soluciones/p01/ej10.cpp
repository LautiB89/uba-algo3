#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "mis-aux.cpp"

using namespace std;

const int BOTTOM = -1;

/* 
Idea del algoritmo backtracking
Tomo uno de las i cajas disponibles entre 1 y N
    Ademas tienen q ser mayores a la ultima caja en mi sol parcial
La agrego a mi solucion parcial y hago la recursion marcando la caja i como tomada

Si no hay cajas disponibles veo que sea una solucion valida y si es la mas optima, la guardo

Tmb podria agregar podas:
    - Por factibilidad: ir guardando el peso "restante" para cada caja en la pila y chequear que al agregar la proxima caja, no se rompa ninguno de los pesos (creo que puedo tomar el minimo)
    - Por optimalidad: veo si agrear todas las cajas disponibles no supera a la solucion optima

Formulación recursiva:
Puedo ir devolviendo  donde
    c es la cantidad de cajas maxima
Recibo (n, k) donde 
    n es la cantidad de cajas actual
    p es el peso total de mi pila

pesos es w y soportes es s
cajas(n, p)
    | p <  0    = -1 
    | n == 0    =  0
    | s[n] < p  = cajas(n-1, k)
    | otherwise = max(cajas(n-1, k), cajas(n-1, k + w[n]) + 1)

Cajas(n, p) toma el peso de una pila y la cantidad de elementos que falta decidir si van o no.
Devuelve la maxima pila que se puede hacer usando los n elementos restantes y poniendole una pila de peso p arriba.
 */

int cajas = 5;
vector<int> w = {19, 7, 5, 6, 1};
vector<int> s = {15, 13, 7, 8, 2};
int wSum = vecSum(w);
vector<vector<int>> memo(cajas + 1, vector<int>(wSum + 1, BOTTOM));
vector<int> memoBU(wSum + 1, 0);

int pilaPD(int n, int k) {
    // temporal y espacial son lo mismo:
    // O(|w|+1 * max(w)+1)
    if (k < 0)
        return BOTTOM;
    if (n == 0)
        return 0;
    if (memo[n][k] == BOTTOM) {
        memo[n][k] = k > s[n-1] ? 
                pilaPD(n-1, k) :
                max(pilaPD(n-1, k), pilaPD(n-1, k + w[n-1]) + 1);
    }
    return memo[n][k];
}

int pilaBU(int n){ 
    // mi memo arranca todo en 0
    vector<int> oldMemo;
    int subSum = wSum;
    for (int i = 1; i <= n; i++) {
        oldMemo = memoBU;
        // en realidad solo recorre los valores que se pueden formar sumando los ultimos i elementos
        // podría acotar usando la suma total del subarreglo [i-1, n] de w 
        subSum -= w[i-1];
        for (int k = 0; k <= subSum; k++) {
            memoBU[k] = k > s[i-1] ?
                oldMemo[k] :
                max(oldMemo[k], oldMemo[k + w[i-1]] + 1);
        }                
        printf("Suma maxima para i = %d es %d\n", i, subSum);
    }
    return memoBU[0];
}

int main() {
    pilaPD(cajas, 0);
    showMat(memo);
    cout << "\n";
    pilaBU(cajas);
    showVec(memoBU);

}
