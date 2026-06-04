#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

El problema se modela como un problema de mochila entera 0/1. Cada cofre
 puede cogerse como mucho una vez, tiene como valor la cantidad de oro que
 contiene y tiene como coste temporal el tiempo necesario para bajar y subir
 hasta él. Si un cofre está a profundidad p, el tiempo total necesario para
 recogerlo es p + 2p = 3p.

 Definimos bajadas(i, j) como la máxima cantidad de oro que se puede conseguir
 considerando únicamente los i primeros cofres y disponiendo de j segundos de
 aire. Para calcular cada estado hay dos posibilidades: no coger el cofre i, en
 cuyo caso el valor es bajadas(i - 1, j), o cogerlo si su tiempo cabe en j, en
 cuyo caso el valor es bajadas(i - 1, j - 3p_i) + oro_i. Nos quedamos con el
 máximo de ambas opciones.

 La solución se obtiene mediante programación dinámica con memorización,
 guardando en una matriz los subproblemas ya resueltos. Una vez calculado el
 valor óptimo, se reconstruye una solución recorriendo la matriz desde
 bajadas(N, T) hacia atrás, comprobando qué cofres han sido utilizados.

 Si N es el número de cofres y T el tiempo máximo disponible, hay N*T estados
 distintos y cada uno se calcula en tiempo constante. Por tanto, el coste en
 tiempo es O(N*T). La memoria adicional utilizada por la matriz de programación
 dinámica es O(N*T), más O(N) para guardar la solución reconstruida.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Objeto {
    int p, oro;
};

int mochila_rec(vector<Objeto> const& obj, int i, int j, Matriz<int>& bajadas) {
    if (bajadas[i][j] != -1)
        return bajadas[i][j];

    if (i == 0 || j == 0)
        bajadas[i][j] = 0;
    else if ((obj[i - 1].p + 2 * obj[i - 1].p) > j)
        bajadas[i][j] = mochila_rec(obj, i - 1, j, bajadas);
    else 
        bajadas[i][j] = max(mochila_rec(obj, i - 1, j, bajadas), mochila_rec(obj, i - 1, j - (obj[i - 1].p + 2* obj[i - 1].p), bajadas) + obj[i - 1].oro);
        
    return bajadas[i][j];
}

int mochila(vector<Objeto> const& obj, int N, int T, vector<Objeto> & sol) {
    Matriz<int> bajadas(N + 1, T + 1, -1);
    int oT = mochila_rec(obj, N, T, bajadas);

    int i = N, j = T;
    while (i > 0 && j > 0) {
        if (bajadas[i][j] != bajadas[i - 1][j]) {
            sol.push_back(obj[i - 1]);
            j -= (obj[i - 1].p + 2 * obj[i - 1].p);
        }
        i--;
    }

    return oT;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int T, N;
    cin >> T >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<Objeto> obj(N);
    for (int i = 0; i < N; i++) {
        cin >> obj[i].p >> obj[i].oro;
    }

    vector<Objeto> sol;
    int oroT = mochila(obj, N, T, sol);

    cout << oroT << endl;
    if (oroT > 0) {
        cout << sol.size() << endl;
        for (int i = 0; i < sol.size(); i++)
            cout << sol[i].p << " " << sol[i].oro << endl;
    }
    else cout << "0" << endl;

    cout << "---" << endl;


    // escribir la solución

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open())
        cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
