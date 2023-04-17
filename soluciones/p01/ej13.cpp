#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "mis-aux.cpp"

using namespace std;

const int BOTTOM = -1;

bool bailan(int a, int b) {
    return abs(a - b) <= 1;
}

int maxParejas(vector<int> h1, vector<int> h2) {
    int res = 0, i1 = 0, i2 = 0, n1 = h1.size(), n2 = h2.size();
    while (i1 < n1 && i2 < n2) {
        if (bailan(h1[i1], h2[i2])) {
            res++;
            i1++;
            i2++;
        } else if (h1[i1] < h2[i2])
            i1++;
        else
            i2++;
    }
    return res;
}

void test1(){
    printf("Prueba 1: \n");
    vector<int> a = {1,2,4,6};
    vector<int> b = {1,5,5,7,9};
    showVec(a);
    showVec(b);
    cout << maxParejas(a, b) << endl;
}

void test2(){
    printf("Prueba 2: \n");
    vector<int> a = {1,1,1,1,1};
    vector<int> b = {1,2,3};
    showVec(a);
    showVec(b);
    cout << maxParejas(a, b) << endl;
}

int main() {
    test1();
    test2();
}
