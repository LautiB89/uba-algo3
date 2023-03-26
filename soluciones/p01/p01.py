sol = list(set())
solParcial = set()

def sumaSubconjConCopia(s : set[int], k: int):
    global solParcial, sol
    # si no tengo mas cosas para sacar, solo queda fijarme si llegue a una solucion
    if len(s) == 0:
        if sum(solParcial) == k:
            print("Encontre una solucion: ", solParcial)
            sol.append(solParcial.copy())    
        return sol
    
    nextItem = s.pop()
    s2 = s.copy()
    solParcial.add(nextItem)
    sumaSubconjConCopia(s2, k)
    solParcial.remove(nextItem)
    sumaSubconjConCopia(s2, k)

    return sol

def sumaSubconj(s : list[int], k: int, i = 0):
    global solParcial, sol
    # si no tengo mas cosas para sacar, solo queda fijarme si llegue a una solucion
    if len(s) == i:
        if sum(solParcial) == k:
            print("Encontre una solucion: ", solParcial)
            sol.append(solParcial.copy())    
        return sol
    
    nextItem = s[i]
    solParcial.add(nextItem)
    sumaSubconj(s, k, i+1)
    solParcial.remove(nextItem)
    sumaSubconj(s, k, i+1)

    return sol


if __name__ == "__main__":
    print(sumaSubconj(list({1,2,3}), 3))