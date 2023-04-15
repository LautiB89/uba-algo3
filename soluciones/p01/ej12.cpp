
/* 
Distinguibles: acá importa el orden
    1 1 4 es distinto 1 4 1
n = #dados
k = valor max de los dados
s = suma que queremos hacer de una tirada

f(n, s) devuelve las permutaciones de n eltos 
tal que la suma da s

f(n, s)
    | (s <= 0)  = 0
    | (n == 1)  = (s <= k)  (sii s puede salir en un dado)
    | otherwise = sum_i=1^k( f(n-1, s-i) )

Vale!!!
k = 4
f(3, 6) =
    f(2, 5) 4
        f(1, 4) 1
        f(1, 3) 1
        f(1, 2) 1
        f(1, 1) 1
    f(2, 4) 3
        f(1, 3) 1
        f(1, 2) 1
        f(1, 1) 1
        f(1, 0) 0
    f(2, 3) 2
        f(1, 2)  1
        f(1, 1)  1
        f(1, 0)  0
        f(1, -1) 0
    f(2, 2) 1
        f(1, 1)  1
        f(1, 0)  0
        f(1, -1) 0
        f(1, -2) 0

f(n, s, k) ahora tambien pasamos los valores de los dados
esto nos permite acotar los valores 
que pueden tomar los dados del paso recursivo

f(n, s, k)
    | (s <= 0) || (k <= 0) = 0
    | (n == 1)  = (s <= k)  (sii s puede salir en un dado)
    | otherwise = sum_i=1^k( f(n-1, s-i, i) )

Vale!!! 
f(3, 6, 4) 2
    1 f(2, 5, 1)
        1 f(1, 4, 1) 0

    2 f(2, 4, 2)
        1 f(1, 3, 1) 0
        2 f(1, 2, 2) 1

    3 f(2, 3, 3)
        1 f(1, 2, 1) 0
        2 f(1, 1, 2) 1
        3 f(1, 0, 3) 0

    4 f(2, 2, 4)
        1 f(1, 1, 1) 1
        2 f(1, 0, 2) 0
        3 f(1, -, 3) 0
        4 f(1, -, 4) 0
    

 */