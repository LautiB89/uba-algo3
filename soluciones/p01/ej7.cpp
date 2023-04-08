#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "mis-aux.cpp"
using namespace std;

/* 
Si los tengo c asteroides en el dia j con c not in [0,j] entonces:
    - "debo" asteroides, algo que no está permitido
    - o no voy a poder vender todos los que tengo
Asi que nunca puedo permitir un c que no esté en [0,j]

mgn(j, c) = maximo entre
    - mgn(j-1, c-1) // vender un asteroide en el dia j
    - mgn(j-1, c+1) // comprar un asteroide en el dia j - aca sumo ganancia
    - mgn(j-1, c)   // no hacer nada en el dia j

p = {3,2,5,6}
mgn(4, 0) = 
    mgn(3, 1) + 6 es lo que da p_4 y me gané por venderlo
    mgn(3, 0)

mgn(3, 1) =
    mgn(2, 0) - 5 perdi 5 por comprar p_3
    mgn(2, 2) + 5 gane  5 por vender p_3
    mgn(2, 1)

mgn(2, 2) = mgn(1, 1) + mgn


mgn(j, c) | (j == 0)   = 0
          | (j == c)   = mgn(j-1, c-1) + p[j]
          | (j == c-1) = mgn(j-1, c)   + p[j]
          | (j/2 > c)  = max(mgn(j-1, c+1) - p[j], mgn(j-1, c))
          | (j)  = max(mgn(j-1, c+1) - p[j], mgn(j-1, c))
          | otherwise  = max(mgn(j-1, c+1) - p[j], mgn(j-1, c), mgn(j-1, c-1) + p[j])

(4,0)
    (3,1) - 6
        (2,0) - 6 + 5
            (1,1) - 6 + 5 - 2
                (0,0) - 6 + 5 - 2 + 3 = 0
            (1,0) - 6 + 5
                (0,1) - 6 + 5
                (0,0) - 6 + 5

        (2,2) - 6 - 5
        (2,1) - 6
    (3,0)

 */


int main() {

}