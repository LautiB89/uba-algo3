#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "mis-aux.cpp"

using namespace std;

// No tengo ni idea de si está bien

// Veo en cuantas relaciones está cada uno recorriendo la lista de relaciones

int n; // cantidad de alumnos (nombrados de 1 a n)
vector<vector<bool>> conectan;

vector<int> cantsConexiones() {
    vector<int> res(n+1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            if (conectan[i][j]) {
                conectan[j][i] = true;
                res[i]++; res[j]++;
            }
        }
    }
    showVec(res);
    return res;
}

// mis dos conjuntos solucion
vector<int> A(0), B(0);

void separarCursos() {
    vector<int> cants = cantsConexiones(); // O(n)
    int a = 0, b = 0;

    for (int i = 1; i <= n; i++) { // O(n)
        if (cants[i] > cants[a]) {
            b = a;
            a = i;
        } else if (cants[i] > cants[b])
            b = i;
    }
    A.push_back(a);
    B.push_back(b);
    // en a y b quedaron los representantes (alumnos con más relaciones)
    // de los vectores A y B
    int sumA = cants[a], sumB = cants[b];
    for (int i = 1; i <= n; i++) {
        if (i == a || i == b) continue;

        if (conectan[i][a] && conectan[i][b]) {
            if (sumA < sumB) {
                A.push_back(i); sumA += cants[i];
            } else {
                B.push_back(i); sumB += cants[i];
            }
        }
        else if (conectan[i][a]) {
            A.push_back(i); sumA += cants[i];
        } else {
            B.push_back(i); sumB += cants[i];
        }
    }
}

int test1() {
    n = 4;
    conectan = vector<vector<bool>> (n+1, vector<bool>(n+1, false));
    conectan[1][2] = true;
    conectan[2][3] = true;
    conectan[3][4] = true;
    separarCursos();
    showVec(A);
    showVec(B);
    return 0;
}

int test2() {
    n = 8;
    conectan = vector<vector<bool>> (n+1, vector<bool>(n+1, false));

    conectan[1][2] = true;

    conectan[2][3] = true;
    conectan[2][5] = true;
    conectan[2][8] = true;
    
    conectan[3][4] = true;
    conectan[3][5] = true;
    conectan[3][6] = true;

    conectan[4][7] = true;

    conectan[6][8] = true;
    separarCursos();
    showVec(A);
    showVec(B);
    return 0;
}

int main() {
    test2();
    return 0;
}