#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "mis-aux.cpp"

using namespace std;

const int BOTTOM = -1;

vector<vector<int>> terreno = {
    {-2, -3,  3},
    {-5, -10, 1},
    {10, 30, -5},
};
int n = terreno.size(), m = terreno[0].size();
vector<vector<int>> memo(n, vector<int>(m, BOTTOM));

int minVida(int row, int col) {
    if (row < 0 || col < 0)
        return -1;
    if (row == 0 && col == 0)
        memo[row][col] = max(1, 1 - terreno[0][0]);
    else if (row == 0)
        memo[row][col] = max(1, minVida(row, col-1) - terreno[row][col]);
    else if (col == 0)
        memo[row][col] = max(1, minVida(row-1, col) - terreno[row][col]);
    else if (memo[row][col] == BOTTOM)
        memo[row][col] = max(1, min(minVida(row, col-1), minVida(row-1, col)) - terreno[row][col]);
    return memo[row][col];
}

int bottomUp() {
    vector<int> memoBU(m, -1);
    memoBU[0] = max(1, 1 - terreno[0][0]);
    for(int col = 1; col < m; col++)
        memoBU[col] = max(1, memoBU[col-1] - terreno[0][col]);
    for(int row = 1; row < n; row++) {
        memoBU[0] = max(1, 1 - terreno[0][0]);
        for(int col = 1; col < m; col++)
            memoBU[col] = max(1, min(memoBU[col-1], memoBU[col]) - terreno[row][col]);
    }
    return memoBU[n-1];
}

int main() {
    cout << minVida(n-1, m-1) << endl;
    showMat(memo);
    cout << bottomUp() << endl;
}