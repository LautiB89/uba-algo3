#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "mis-aux.cpp"

using namespace std;

/* 
Estrategia:
la mejor forma es siempre ir haciendo la suma de menor costo posible en cada caso
para un vector de n elementos tenemos q hacer n-1 sumas
el costo de la primera suma va a estar dentro del costo de las n-2 sumas siguientes
el costo de la segunda suma va a estar dentro del costo de las n-3 sumas siguientes
y asi...
de esta forma vemos que lo mas conveniente es que la suma de menor costo sea la primera
la segunda mas chica deberia ser la segunda
etc...

claramente hay que hacer una suma tomando pares de elementos con el vector ordenado

No se que quieren q haga, si es devolver el vector en el orden que hay que sumarlo
entonces solamente es un sort

Si es devolver la suma haciendola con el menor costo
entonces hay que hacer sort y despues una suma
 */

int suma(const vector<int>& v) {
    int sum = 0;
    for (int elem: v)
        sum += elem;
    return sum;
}

int main() {
    return 0;
}