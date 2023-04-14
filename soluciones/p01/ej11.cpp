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

/*     
Para topdown
usar un memo de strings es O(n²k) espacial ya que una string tiene tamaño O(n)
y mas o menos O(n²k) temporal tmb, xq recorremos toda la matriz (nk) 
y las operaciones en string cuestan O(n)

Podriamos hacer lo mismo bottom up, pero tmb podemos:
    - Asegurarnos de poder crear esa lista de ops 
    - generamos la solucion usando nuestra matriz sii existe solucion
para poder generar la solucion tenemos que usar al menos O(nk) para la matrix de booleanos
despues recorremos la solucion para atras en O(n) amortizado
 */

vector<vector<bool>> memoBU(n+1, vector<bool>(w + 1, false));

bool opsBU(int n, int w) {
    // Si hacemos 0 operaciones podemos generar solamente nuestro primer elto
    memoBU[0][v[0]] = true;
    if (n > 1) {
        memoBU[1][v[0] + v[1]] = true;
        memoBU[1][v[0] * v[1]] = true;
        memoBU[1][(pow(v[0], v[1]))] = true;
    }
    int a, b, c;
    // int max_w = max(v[0] + v[1], max(v[0] - v[1], int(pow(v[0], v[1]))));
    for (int row = 1; row < n-1; row++) {
        for (int col = 0; col <= w; col++) {
            if (!memoBU[row][col]) continue;
            a = col + v[row + 1],
            b = col * v[row + 1],
            c = pow(col, v[row + 1]);
            if (a <= w) memoBU[row + 1][a] = true;
            else a = w+1;
            if (b <= w) memoBU[row + 1][b] = true;
            else b = w+1;
            if (c <= w) memoBU[row + 1][c] = true;
            else c = w+1;
        //            max_w = max(a, max(b, c));
        }
        // n_items *= 3; //podria ir contando exactamente cuantos veo pero no es para tanto
    }
    return memoBU[n-1][w];
}

string reconstruir() {
    if (!opsBU(n, w)) return BOTTOM;
    string sol = "";
    int lookUp = w, newLookUp;
    float aux;
    for (int i = n-1; i > 0; i--) {
        if (!memoBU[i][lookUp]) continue;

        newLookUp = lookUp - v[i];
        if (newLookUp > 0 && opsBU(i, newLookUp)) {
            sol = SUM + sol;
            lookUp = newLookUp;
            continue;
        }
        newLookUp = lookUp / v[i];
        if (lookUp % v[i] == 0 && opsBU(i, newLookUp)) {
            sol = MUL + sol;
            lookUp = newLookUp;
            continue;
        }
        // supongo q v[i-1] > 0
        aux = pow(lookUp, 1.0 / v[i]);
        newLookUp = floor(aux);
        if (fmod(aux, 1) == 0 && opsBU(i, newLookUp)) {
            sol = POT + sol;
            lookUp = newLookUp;
        }
    }
    return sol;
}

int main() {
    cout << "Solucion final: " << opsBU(n, w) << endl;
    for (auto row: memoBU) {
        for (int i = 0; i < w+1; i++) {
            if (row[i])
                cout << i << ", ";
        }
        cout << "\n";
    }
    cout << reconstruir() << endl;
}