#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <tuple>
#include "mis-aux.cpp"

using namespace std;
/* 
(c', q)
c' es el minimo valor que podemos formar
q  es la cantidad minima de billetes que usamos para formar c'

ccR(B, c) 
  | (c <= 0)  = (0, 0)
  | (null B)  = no hay solución
  | otherwise = min(ccR(B - {b_n}, c), ccR(B - {b_n}, c - b_n) + (b_n, 1))

ccR({2, 3, 4, 5, 10, 20}, 14) = 
  min(
    ccR({2, 3, 4, 5, 10, 20}, 14),
    ccR({2, 3, 4, 5, 10}, 14-20) + (20, 1)
  ) = 
  min(
    ccR({2, 3, 4, 5, 10, 20}, 14),
    (0, 0) + (20, 1)
  ) = 
  min(
    ccR({2, 3, 4, 5, 10, 20}, 14),
    (20, 1)
  )

{2,3,4,5}, 14
  {2,3,4}, 14
    {2,3}, 14 = none
      {2}, 14 = none
        {}, 14 = none
        {}, 12 = none
      {2}, 11
        {}, 11 = none
        {}, 9  = none
    {2,3}, 10
      
  {2,3,4}, 9

{2,3,4,5}, 4 = min((4,1), (0,0)+(5,1)) = (4,1)
  {2,3,4}, 4 = (4,1)
    ...
  {2,3,4}, -1 = (0,0)
    ...
 */

// Queremos encontrar las soluciones con menor exceso
// y de esas encontrar la que usa menos billetes


tuple<int, int> minTup(tuple<int,int> a, tuple<int,int> b){
  if (get<1>(a) == -1)
    return b;
  if (get<1>(b) == -1)
    return a;
  if (get<0>(a) < get<0>(b))
    return a;
  else if (get<0>(a) > get<0>(b))
    return b;
  else
    return (get<1>(a) < get<1>(b)) ? a : b;
}

tuple<int, int> usarBillete(tuple<int,int> b, int billete) {
  return (get<1>(b) == -1 || get<0>(b) == -1) ? 
            make_tuple(-1, -1) :
            make_tuple(get<0>(b) + billete, get<1>(b) + 1);
}

// la complejidad es O(2^n) con n = |B|

vector<int> B = {100,2,200,3,5,10,20,20,4,5,1,3,20,45,33,11,2,7,9,11,100,2,200,3,5,10,20,20,4,5,1,3,20,45,33,11,2,7,9,11,1,1,1,2,3,4,1,1,1};

tuple<int, int> billetesFuncionBT(int i, int quedaPagar){
  printf("i = %d, quedaPagar = %d\n", i, quedaPagar);
  if (quedaPagar <= 0)
    return make_tuple(0, 0);
  if (i == -1) //ya usamos todo B y no pudimos pagar
    return make_tuple(-1, -1); //(-1,-1) es no solucion
  else {
    tuple<int, int> a = billetesFuncionBT(i-1, quedaPagar);
    tuple<int, int> b = billetesFuncionBT(i-1, quedaPagar-B[i]);
    /* printf("Cuando recibo i=%d y quedaPagar=%d a=(%d, %d) y b=(%d, %d)\n", 
            i, quedaPagar, get<0>(a), get<1>(a), 
            get<0>(usarBillete(b, B[i])), get<1>(usarBillete(b, B[i])));
 */
    return minTup(a, usarBillete(b, B[i]));
  }
}

// toDo : hacer lo mismo en BT pero por referencia

int c = 3730;
vector<vector<tuple<int, int>>> memo(B.size()+1, vector<tuple<int,int>>(c+1, {-2,-2}));

tuple<int, int> billetesDP(int i, int quedaPagar) {
  //no le gusta esto
  printf("i = %d, quedaPagar = %d\n", i, quedaPagar);
  
  if (memo[i+1][quedaPagar] != make_tuple(-2, -2)) 
    return memo[i+1][quedaPagar];
  
  if (quedaPagar <= 0) {
    memo[i+1][quedaPagar] = make_tuple(0, 0);
    return (make_tuple(0, 0));
  }
  if (i == -1) {
    memo[i+1][quedaPagar] = make_tuple(-1, -1);
    return (make_tuple(-1, -1));
  } //ya usamos todo B y no pudimos pagar
    //return (make_tuple(-1, -1)); //(-1,-1) es no solucion
  else {
    tuple<int, int> a = billetesDP(i-1, quedaPagar);
    tuple<int, int> b = billetesDP(i-1, quedaPagar-B[i]);
    printf("Cuando recibo i=%d y quedaPagar=%d a=(%d, %d) y b=(%d, %d)\n", 
            i, quedaPagar, get<0>(a), get<1>(a), 
            get<0>(usarBillete(b, B[i])), get<1>(usarBillete(b, B[i])));

    memo[i+1][quedaPagar] = (minTup(a, usarBillete(b, B[i])));
    return memo[i+1][quedaPagar];
  }
}

int main() {
  printf("que odna\n");
  tuple<int,int> sol = billetesFuncionBT(B.size()-1, c);
  printf("Para pagar %d pago con %d usando %d billetes\n", c, get<0>(sol), get<1>(sol));
  
  /* 
  for (int c = 0; c < 20; c++){
    tuple<int,int> sol = billetesFuncionBT(B.size()-1, c);
    printf("Para pagar %d pago con %d usando %d billetes\n", c, get<0>(sol), get<1>(sol));
  }
  // tmb probamos que no tenga 
  tuple<int,int> sol = billetesFuncionBT(B.size()-1, 8000000);
  printf("Para pagar %d pago con %d usando %d billetes\n", 8000000, get<0>(sol), get<1>(sol));
   */
  return 0;
}